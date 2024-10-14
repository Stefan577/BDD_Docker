import argparse
import concurrent.futures
from enum import StrEnum, auto
import multiprocessing
import os
import platform
import random
import subprocess
import sys

from .cnf import CNF, from_dimacs
from .utils import Timer, file_or_dir_name, human_duration

__version__ = "0.0.1"

TMP_DIR = "tmp"
OUTPUT_DIR = "output"
DOCKER_IMAGE = "sjahns/dimagic_mince"
VERBOSE = False


# heuristics
class Heuristics(StrEnum):
    NONE = auto()
    MINCE = auto()
    FORCE = auto()


# default arguments
DEFAULT_SEED = 4711
DEFAULT_HEURISTIC = Heuristics.NONE

# Choose pmc executable
current_os = platform.system()
if current_os == "Linux":
    PMC = "bin/pmc_linux"
elif current_os == "Darwin":  # macOS
    PMC = "bin/pmc_mac"
else:
    raise OSError(f"Unsupported operating system: {current_os}")


def main():
    global OUTPUT_DIR
    # set up argument parsing
    arg_parser = argparse.ArgumentParser(
        prog="dimagic",
        description="Preprocess DIMACS files for efficient BDD construction.",
        add_help=False,
    )
    arg_parser.add_argument(
        "input", help="the input DIMACS file, or a folder containing DIMACS files"
    )
    arg_parser.add_argument(
        "--benchmark-suite",
        action="store_true",
        help="create a benchmark suite with the flags -p, -v, and -c applied in almost all combinations (-v is either FORCE or MINCE, -c is either NONE, FORCE or MINCE)",
    )
    arg_parser.add_argument(
        "--seed",
        action="store",
        metavar="SEED",
        type=int,
        default=DEFAULT_SEED,
        help=f"random seed (not used for MINCE!) (default: {DEFAULT_SEED})",
    )
    arg_parser.add_argument(
        "--cores",
        action="store",
        type=int,
        default=0,
        help="number of cores to use for parallel processing. A value of 0 (default) tries to choose as many cores as are available",
    )

    processing_group = arg_parser.add_argument_group(
        "toggle which processing steps are applied (the order of processing follows the order given here)"
    )
    processing_group.add_argument(
        "-rv",
        "--random-variable-ordering",
        action="store_true",
        help="randomize the initial variable ordering",
    )
    processing_group.add_argument(
        "-rc",
        "--random-clause-ordering",
        action="store_true",
        help="randomize the initial clause ordering",
    )
    processing_group.add_argument(
        "-p", "--pmc", action="store_true", help="apply PMC preprocessing"
    )
    processing_group.add_argument(
        "-v",
        "--variable-order",
        choices=list(Heuristics),
        default=DEFAULT_HEURISTIC,
        help=f"the variable order heuristic (default: {DEFAULT_HEURISTIC})",
    )
    processing_group.add_argument(
        "-c",
        "--clause-order",
        choices=list(Heuristics),
        default=DEFAULT_HEURISTIC,
        help=f"the clause order heuristic (default: {DEFAULT_HEURISTIC})",
    )

    output_group = arg_parser.add_argument_group("output options")
    output_group.add_argument(
        "-o",
        "--output_dir",
        metavar="PATH",
        help=f"output directory (default: {OUTPUT_DIR}/)",
    )
    output_group.add_argument(
        "-l2b",
        "--logic2bdd",
        action="store_true",
        help="also export vars and expressions in the BDD_Docker format",
    )

    info_group = arg_parser.add_argument_group("info parameters")
    info_group.add_argument(
        "--verbose", action="store_true", help="show output from MINCE"
    )
    info_group.add_argument(
        "-h", "--help", action="help", help="show this help message"
    )
    info_group.add_argument(
        "--version", action="version", version="%(prog)s " + __version__
    )

    # parse arguments
    args = arg_parser.parse_args()
    if args.variable_order or args.clause_order:
        check_docker()
    if args.verbose:
        global VERBOSE
        VERBOSE = True
    if args.output_dir:
        OUTPUT_DIR = args.output_dir
    random.seed(args.seed)

    # create tmp directory
    if not os.path.exists(TMP_DIR):
        os.makedirs(TMP_DIR)

    # Get the number of available CPU cores
    if args.cores == 0:
        args.cores = multiprocessing.cpu_count()

    if args.benchmark_suite:
        create_benchmark(args)
    else:
        process(args)


def process(args):
    # collect input files
    input_path = args.input
    dimacs_paths = []
    if os.path.isdir(input_path):
        for file in os.listdir(input_path):
            if file.endswith(".dimacs") or file.endswith(".cnf"):
                dimacs_paths.append(os.path.join(input_path, file))
    else:
        dimacs_paths.append(input_path)
        input_path = os.path.dirname(input_path)

    # create output folder
    output_path = output_dir(input_path, args)

    # Iterate over all DIMACS files
    for dimacs_path in dimacs_paths:
        skip = False  # signal to skip subsequent steps
        print("\nProcessing", dimacs_path)
        timer = Timer(output_string="Overall time:")
        dimacs_name = file_or_dir_name(dimacs_path)

        # parse CNF
        cnf = from_dimacs(dimacs_path)
        print(" Variables:", cnf.num_variables)
        print(" Clauses:", cnf.num_clauses)
        # print(" Equiv classes:", cnf.equiv_clause_count())

        # randomize ordering?
        if args.random_variable_ordering or args.random_clause_ordering:
            if args.random_variable_ordering:
                print("Randomly shuffling variable order")
                random.shuffle(cnf.var_ordering)
            if args.random_clause_ordering:
                print("Randomly shuffling clause order")
                random.shuffle(cnf.clauses)
            # overwrite dimacs_path with new file with the shuffled orders
            dimacs_path = os.path.join(TMP_DIR, dimacs_name + ".dimacs")
            cnf.to_dimacs(dimacs_path)

        # preprocess with pmc
        if args.pmc:
            pmc_cnf, pmc_dimacs_path = run_pmc(dimacs_path, dimacs_name)
            pmc_cnf.set_var_names(cnf.var_names)
            if pmc_cnf.num_clauses == 0:
                print("No clauses remaining after running pmc!")
                skip = True
            dimacs_path = pmc_dimacs_path
            cnf = pmc_cnf

        # compute variable ordering
        if args.variable_order != Heuristics.NONE and not skip:
            if args.variable_order == Heuristics.MINCE:
                var_ordering = var_ordering_mince(dimacs_path)
            elif args.variable_order == Heuristics.FORCE:
                var_ordering = var_ordering_force(cnf)
            else:
                assert False
            if not var_ordering:
                continue
            cnf.set_var_ordering(var_ordering)

        # compute clause ordering
        if args.clause_order != Heuristics.NONE and not skip:
            if args.clause_order == Heuristics.MINCE:
                clause_ordering = clause_ordering_mince(cnf, dimacs_name)
            elif args.clause_order == Heuristics.FORCE:
                clause_ordering = clause_ordering_force(cnf)
            else:
                assert False
            if clause_ordering is None:
                continue
            cnf.set_clause_ordering(clause_ordering)

        # write new DIMACS files that includes the computed variable and clause ordering
        output_file = os.path.join(output_path, dimacs_name + ".dimacs")
        print("Writing preprocessed DIMACS file to", output_file)
        cnf.to_dimacs(output_file)

        # export in BDD_Docker format
        if args.logic2bdd:
            cnf.to_logic2bdd(output_file)
        timer.stop()


def create_benchmark(args):
    print("Creating benchmark suite for", args.input)
    timer_all = Timer(enable_printing=False)

    # collect input files
    input_path = args.input
    dimacs_paths = []
    if os.path.isdir(input_path):
        for file in os.listdir(input_path):
            if file.endswith(".dimacs") or file.endswith(".cnf"):
                dimacs_paths.append(os.path.join(input_path, file))
    else:
        dimacs_paths.append(input_path)
        input_path = os.path.dirname(input_path)
    num_files = len(dimacs_paths)

    # create all output directories
    dirs = dict()
    args.pmc = False
    args.variable_order = Heuristics.FORCE
    args.clause_order = Heuristics.NONE
    dirs["vf"] = output_dir(input_path, args)

    args.pmc = True
    args.variable_order = Heuristics.FORCE
    args.clause_order = Heuristics.NONE
    dirs["p_vf"] = output_dir(input_path, args)

    args.pmc = False
    args.variable_order = Heuristics.MINCE
    args.clause_order = Heuristics.NONE
    dirs["vm"] = output_dir(input_path, args)

    args.pmc = True
    args.variable_order = Heuristics.MINCE
    args.clause_order = Heuristics.NONE
    dirs["p_vm"] = output_dir(input_path, args)

    args.pmc = False
    args.variable_order = Heuristics.FORCE
    args.clause_order = Heuristics.FORCE
    dirs["vf_cf"] = output_dir(input_path, args)

    args.pmc = True
    args.variable_order = Heuristics.FORCE
    args.clause_order = Heuristics.FORCE
    dirs["p_vf_cf"] = output_dir(input_path, args)

    args.pmc = False
    args.variable_order = Heuristics.MINCE
    args.clause_order = Heuristics.MINCE
    dirs["vm_cm"] = output_dir(input_path, args)

    args.pmc = True
    args.variable_order = Heuristics.MINCE
    args.clause_order = Heuristics.MINCE
    dirs["p_vm_cm"] = output_dir(input_path, args)

    log_dir = os.path.join(OUTPUT_DIR, "log")
    if not os.path.exists(log_dir):
        os.makedirs(log_dir)

    # process files in parallel
    incomplete = []
    print(f"Processing {num_files} files in parallel using {args.cores} workers ...")
    with concurrent.futures.ProcessPoolExecutor(max_workers=args.cores) as executor:
        # Submit all file processing tasks to the executor
        futures = {
            executor.submit(
                create_benchmark_file, dimacs_path, dirs, args, log_dir
            ): dimacs_path
            for dimacs_path in dimacs_paths
        }

        # Collect results as they are completed
        completed = 0
        for future in concurrent.futures.as_completed(futures):
            file = futures[future]
            try:
                result = future.result()
                if not result:
                    incomplete.append(file)

            except Exception as exc:
                print(f"{file} raised an exception: {exc}")
            finally:
                completed += 1
                print(
                    f"completed {completed}/{num_files} ({(completed/num_files) * 100:.2f}%) after {human_duration(timer_all.stop())}"
                )

    print("\nBenchmark suite complete:")
    print("\n".join(dirs.values()))

    if len(incomplete) > 0:
        print(
            "For the following files some benchmarks could not be created due to errors:"
        )
        print("\n".join(incomplete))


def create_benchmark_file(dimacs_path, output_dirs, args, log_dir):
    name = file_or_dir_name(dimacs_path)
    log_file_path = os.path.join(log_dir, name + ".log")
    with open(log_file_path, "a") as log_file:
        log_print = lambda *s: print(*s, file=log_file)

        complete = True  # flag to indicate whether all benchmarks could be created
        log_print("\nProcessing", dimacs_path)
        timer = Timer(output_string="Overall time:", output_function=log_print)
        dimacs_file_name = os.path.basename(dimacs_path)
        dimacs_name, _ = os.path.splitext(dimacs_file_name)

        # parse CNF
        cnf = from_dimacs(dimacs_path)
        log_print(" Variables:", cnf.num_variables)
        log_print(" Clauses:", cnf.num_clauses)

        # randomize ordering?
        if args.random_variable_ordering or args.random_clause_ordering:
            if args.random_variable_ordering:
                log_print("Randomly shuffling variable order")
                random.shuffle(cnf.var_ordering)
            if args.random_clause_ordering:
                log_print("Randomly shuffling clause order")
                random.shuffle(cnf.clauses)
            # overwrite dimacs_path with new file with the shuffled orders
            dimacs_path = os.path.join(TMP_DIR, dimacs_name + ".dimacs")
            cnf.to_dimacs(dimacs_path)
        # var_ordering = cnf.var_ordering.copy()
        clause_ordering = cnf.clause_ordering.copy()

        # run PMC
        pmc_cnf, pmc_dimacs_path = run_pmc(dimacs_path, dimacs_name, log_print)
        pmc_cnf.set_var_names(cnf.var_names)
        if pmc_cnf.num_clauses == 0:
            log_print("Warning: No clauses remaining after running PMC!")
            return False
        # pmc_var_ordering = pmc_cnf.var_ordering.copy()
        pmc_clause_ordering = pmc_cnf.clause_ordering.copy()

        # FORCE var ordering
        force_var_ordering = var_ordering_force(cnf, log_print)
        pmc_force_var_ordering = var_ordering_force(pmc_cnf, log_print)

        # FORCE clause ordering
        force_clause_ordering = clause_ordering_force(cnf, log_print)
        pmc_force_clause_ordering = clause_ordering_force(pmc_cnf, log_print)

        # MINCE var ordering
        mince_var_ordering = var_ordering_mince(dimacs_path, log_print)
        if mince_var_ordering is None:
            complete = False
            mince_var_ordering = []
        pmc_mince_var_ordering = var_ordering_mince(pmc_dimacs_path, log_print)
        if pmc_mince_var_ordering is None:
            complete = False
            pmc_mince_var_ordering = []

        # MINCE clause ordering
        mince_clause_ordering = clause_ordering_mince(cnf, dimacs_name, log_print)
        if mince_clause_ordering is None:
            complete = False
            mince_clause_ordering = []
        pmc_mince_clause_ordering = clause_ordering_mince(
            pmc_cnf, dimacs_name, log_print
        )
        if pmc_mince_clause_ordering is None:
            complete = False
            pmc_mince_clause_ordering = []

        # 1. FORCE variable ordering
        output_file = os.path.join(output_dirs["vf"], dimacs_file_name)
        cnf.set_var_ordering(force_var_ordering)
        cnf.set_clause_ordering(clause_ordering)
        cnf.to_dimacs(output_file)
        if args.logic2bdd:
            cnf.to_logic2bdd(output_file)

        # 2. PMC + FORCE variable ordering
        output_file = os.path.join(output_dirs["p_vf"], dimacs_file_name)
        pmc_cnf.set_var_ordering(pmc_force_var_ordering)
        pmc_cnf.set_clause_ordering(pmc_clause_ordering)
        pmc_cnf.to_dimacs(output_file)
        if args.logic2bdd:
            pmc_cnf.to_logic2bdd(output_file)

        # 3. MINCE variable ordering
        output_file = os.path.join(output_dirs["vm"], dimacs_file_name)
        cnf.set_var_ordering(mince_var_ordering)
        cnf.set_clause_ordering(clause_ordering)
        cnf.to_dimacs(output_file)
        if args.logic2bdd:
            cnf.to_logic2bdd(output_file)

        # 4. PMC + MINCE variable ordering
        output_file = os.path.join(output_dirs["p_vm"], dimacs_file_name)
        pmc_cnf.set_var_ordering(pmc_mince_var_ordering)
        pmc_cnf.set_clause_ordering(pmc_clause_ordering)
        pmc_cnf.to_dimacs(output_file)
        if args.logic2bdd:
            pmc_cnf.to_logic2bdd(output_file)

        # 5. FORCE variable & clause ordering
        output_file = os.path.join(output_dirs["vf_cf"], dimacs_file_name)
        cnf.set_var_ordering(force_var_ordering)
        cnf.set_clause_ordering(force_clause_ordering)
        cnf.to_dimacs(output_file)
        if args.logic2bdd:
            cnf.to_logic2bdd(output_file)

        # 6. PMC + FORCE variable & clause ordering
        output_file = os.path.join(output_dirs["p_vf_cf"], dimacs_file_name)
        pmc_cnf.set_var_ordering(pmc_force_var_ordering)
        pmc_cnf.set_clause_ordering(pmc_force_clause_ordering)
        pmc_cnf.to_dimacs(output_file)
        if args.logic2bdd:
            pmc_cnf.to_logic2bdd(output_file)

        # 7. MINCE variable & clause ordering
        output_file = os.path.join(output_dirs["vm_cm"], dimacs_file_name)
        cnf.set_var_ordering(mince_var_ordering)
        cnf.set_clause_ordering(mince_clause_ordering)
        cnf.to_dimacs(output_file)
        if args.logic2bdd:
            cnf.to_logic2bdd(output_file)

        # 8. PMC + MINCE variable & clause ordering
        output_file = os.path.join(output_dirs["p_vm_cm"], dimacs_file_name)
        pmc_cnf.set_var_ordering(pmc_mince_var_ordering)
        pmc_cnf.set_clause_ordering(pmc_mince_clause_ordering)
        pmc_cnf.to_dimacs(output_file)
        if args.logic2bdd:
            pmc_cnf.to_logic2bdd(output_file)

        timer.stop()
    return complete


class MinceError(Exception):
    pass


def mince(path: str) -> list[int]:
    dir = os.path.dirname(path)
    basename, _ = os.path.splitext(os.path.basename(path))
    output_file = os.path.join(TMP_DIR, basename + ".ord")

    # commands to be executed inside the Docker container
    mince_commands = [
        f"cnf2hgraph.pl {path}",
        "MetaPlacerTest0.exeS -f out.aux -save -branchingFactor 1 -constTol 20 -saveXorder",
        f"mv left2right.ord {output_file}",
    ]
    command = [
        "docker",
        "run",
        "--rm",
        "-v",
        f"{os.path.abspath(dir)}:/{dir}:Z",
        "-v",
        f"{os.path.abspath(TMP_DIR)}:/{TMP_DIR}:Z",
        DOCKER_IMAGE,
        "; ".join(mince_commands),
    ]
    if VERBOSE:
        print("Running:", " ".join(command))
        result = subprocess.run(command, stdout=sys.stdout, stderr=sys.stderr)
    else:
        result = subprocess.run(
            command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
        )
    if result.returncode != 0:
        print(
            "Error: MINCE failed. Try re-running with --verbose to see MINCE output.",
            file=sys.stderr,
        )
        raise MinceError
    return get_order(output_file)


def get_order(path: str) -> list[int]:
    """
    Read order from MINCE output file.

    The file format is as follows:
    ```
              v1
            v819
             v23
           v4711
    ```
    """
    vars = []
    with open(path, "r") as file:
        for line in file:
            line = line.strip()
            if not line:
                # skip empty lines
                continue
            if line[0] != "v":
                print("unexpected line:", line)
            vars.append(int(line[1:]))
    return vars


def check_docker():
    # test if docker is running
    result = subprocess.run(
        ["docker", "stats", "--no-stream"], capture_output=True, text=True
    )
    if result.returncode == 1:
        print(result.stderr, file=sys.stderr)
        exit(1)

    # test if docker image exists
    result = subprocess.run(
        ["docker", "images", "-q", DOCKER_IMAGE], capture_output=True, text=True
    )
    if result.stdout == "":
        print(
            f"Error: Docker image '{DOCKER_IMAGE}' not found.\n"
            + f"Try to download '{DOCKER_IMAGE}'\n"
        )
        result = subprocess.run(
            ["docker", "pull", DOCKER_IMAGE], capture_output=True, text=True
        )
        #code_logic2bdd to download image
        if result.returncode != 0:
            print(f"Error: Could not pull Image: {DOCKER_IMAGE}")
            exit(1)
        else:
            print(f"Download {DOCKER_IMAGE} complete.")


def output_dir(input_path: str, args) -> str:
    # create output folder
    basename, _ = os.path.splitext(os.path.basename(input_path))
    if basename == "":
        basename = os.path.basename(os.path.split(input_path)[0])
        assert basename != ""
    if args.pmc:
        basename += "-p"
    if args.variable_order == "mince":
        basename += "-vm"
    elif args.variable_order == "force":
        basename += "-vf"
    if args.clause_order == "mince":
        basename += "-cm"
    elif args.clause_order == "force":
        basename += "-cf"
    output_path = os.path.join(OUTPUT_DIR, basename)
    if os.path.exists(output_path):
        print(
            f"Warning: Output directory {output_path} already exists, existing files might be overwritten."
        )
    else:
        os.makedirs(output_path)
    return output_path


def run_pmc(file_path, file_name, my_print=print) -> tuple[CNF, str]:
    my_print("Preprocessing with pmc ...")
    timer = Timer(output_string=" finished in", output_function=my_print)
    pmc_dimacs_path = os.path.join(TMP_DIR, file_name + ".pmc.dimacs")
    with open(pmc_dimacs_path, "w") as output_file:
        subprocess.run(
            [
                PMC,
                "-vivification",
                "-eliminateLit",
                "-litImplied",
                "-iterate=10",
                "-verb=0",
                file_path,
            ],
            stdout=output_file,
            stderr=subprocess.DEVNULL,
        )
    pmc_cnf = from_dimacs(pmc_dimacs_path)
    pmc_cnf.to_dimacs(pmc_dimacs_path)
    my_print(" Clauses:", pmc_cnf.num_clauses)
    timer.stop()
    return pmc_cnf, pmc_dimacs_path


def var_ordering_mince(file_path, my_print=print):
    my_print("Computing MINCE variable ordering ...")
    timer = Timer(output_string=" finished in", output_function=my_print)
    try:
        var_ordering = mince(file_path)
    except MinceError:
        return None
    finally:
        timer.stop()
    return var_ordering


def var_ordering_force(cnf: CNF, my_print=print):
    my_print("Computing FORCE variable ordering ...")
    timer = Timer(output_string=" finished in", output_function=my_print)
    hg = hypergraph.from_cnf(cnf.var_ordering, cnf.clauses)
    var_ordering = hg.compute_force_ordering()
    var_ordering = [v + 1 for v in var_ordering]
    timer.stop()
    return var_ordering


def clause_ordering_mince(cnf: CNF, file_name, my_print=print):
    my_print("Computing MINCE clause ordering ...")
    timer = Timer(output_string=" finished in", output_function=my_print)
    clause_dimacs_path = os.path.join(TMP_DIR, file_name + ".clause.dimacs")
    clause_fake_cnf = cnf.generate_clause_cnf()
    clause_fake_cnf.to_dimacs(clause_dimacs_path)
    try:
        clause_ordering = mince(clause_dimacs_path)
    except MinceError:
        return None
    finally:
        timer.stop()
    clause_ordering = [c - 1 for c in clause_ordering]
    return clause_ordering


def clause_ordering_force(cnf: CNF, my_print=print):
    my_print("Computing FORCE clause ordering ...")
    timer = Timer(output_string=" finished in", output_function=my_print)
    clause_cnf = cnf.generate_clause_cnf()
    hg = hypergraph.from_cnf(clause_cnf.var_ordering, clause_cnf.clauses)
    clause_ordering = hg.compute_force_ordering()
    timer.stop()
    return clause_ordering


if __name__ == "__main__":
    main()
