import os
from typing import Optional

VAR_NAME = "UnnamedVariable_"  # prefix for unnamed variables


class CNF:
    def __init__(self, clauses: list[list[int]], num_variables: int, var_names=None):
        self.clauses = clauses
        self.num_variables = num_variables
        self.num_clauses = len(clauses)
        self.var_names: Optional[dict[int, str]] = var_names
        self.var_ordering: list[int] = []  # 1-indexed
        self.clause_ordering: list[int] = list(range(0, self.num_clauses))  # 0-index

        # complete var_names in case some names are missing
        if var_names:
            unnamed_counter = 0
            for i in range(1, num_variables + 1):
                if i not in var_names:
                    unnamed_counter += 1
                    var_names[i] = VAR_NAME + str(unnamed_counter)

        # set default var_ordering
        if var_names:
            self.var_ordering = list(var_names.keys())
        else:
            self.var_ordering = list(range(1, num_variables + 1))

    def set_var_ordering(self, var_ordering: list[int]):
        self.var_ordering = var_ordering

    def set_clause_ordering(self, clause_ordering: list[int]):
        self.clause_ordering = clause_ordering

    def set_var_names(self, var_names: Optional[dict[int, str]]):
        self.var_names = var_names

    def generate_clause_cnf(self):
        # one new clause for every variable
        new_clauses = [set() for _ in range(self.num_variables)]
        # for each original clause ...
        for i in range(0, self.num_clauses):
            # ... add its ID to the new clauses of each of its variables
            for var in self.clauses[i]:
                new_clauses[abs(var) - 1].add(i + 1)
        new_clauses = [sorted(c) for c in new_clauses if c]
        # print("max clause length:", max(map(len, new_clauses)))
        return CNF(new_clauses, num_variables=self.num_clauses)

    def to_dimacs(self, path: str):
        """
        Save the CNF as a file in DIMACS format.
        """
        with open(path, "w") as file:
            # all variable IDs with names in order
            if self.var_names:
                for i in self.var_ordering:
                    file.write(f"c {i} {self.var_names[i]}\n")

            # header line 'p cnf <num vars> <num clauses>'
            file.write(f"p cnf {self.num_variables} {self.num_clauses}\n")

            # all clauses, following the ordering if available
            for i in self.clause_ordering:
                file.write(" ".join(map(str, self.clauses[i])) + " 0\n")

    def to_logic2bdd(self, path: str):
        """
        Save CNF in the Logic2BDD format:
        - `.var` file with the names of the variables in order
        - `.exp` file with the clauses as expressions in order
        """
        base_path, _ = os.path.splitext(path)
        var_path = base_path + ".var"
        exp_path = base_path + ".exp"
        # export variables
        with open(var_path, "w") as var_file:
            assert self.var_names
            unnamed_counter = 0
            for i in self.var_ordering:
                if i in self.var_names:
                    var_file.write(f"{self.var_names[i]}\n")
                else:
                    unnamed_counter += 1
                    name = VAR_NAME + str(unnamed_counter)
                    self.var_names[i] = name
                    var_file.write(f"{name}\n")
        # export clauses as expressions
        with open(exp_path, "w") as exp_file:
            for i in self.clause_ordering:
                literals = [
                    ("not " if n < 0 else "") + self.var_names[abs(n)]
                    for n in self.clauses[i]
                ]
                exp_file.write(" or ".join(literals) + "\n")


def from_dimacs(path, warnings=True) -> CNF:
    var_names = dict()  # mapping from variable IDs to names
    variables = set()
    clauses = []
    num_vars = 0
    num_clauses = 0
    with open(path, "r") as file:
        parse_clauses = False
        for line in file:
            line = line.strip()
            if not line:
                # skip empty lines
                continue
            if line.startswith("c"):
                if parse_clauses:
                    # skip all comments after parsing the header
                    continue
                elif line.startswith("c "):
                    # header can contain variable names
                    # c <ID> <Name> [<stuff> <to> <ignore> ...]
                    if "$" in line:
                        # some lines in data/CDL look like this:
                        # c <ID>$ <name>
                        line = line.replace("$", "")

                    chunks = line.split(" ")
                    if len(chunks) < 3:
                        continue
                    try:
                        id = int(chunks[1])
                        name = chunks[2]
                        var_names[id] = name
                    except:
                        continue
                else:
                    continue

            if line.startswith("p"):
                # p cnf <num vars> <num clauses>
                chunks = line.split(" ")
                if chunks[1] != "cnf" or len(chunks) > 4:
                    print(
                        "Error: expected 'p cnf <num vars> <num clauses>', but got:",
                        line,
                    )
                    exit(1)
                num_vars = int(chunks[2])
                num_clauses = int(chunks[3])
                parse_clauses = True
                continue

            if parse_clauses:
                chunks = line.split(" ")
                if chunks[-1] != "0":
                    print("Error: invalid clause does not end with '0':", line)
                    exit(1)
                clause = list(map(int, chunks[:-1]))
                for i in clause:
                    assert abs(i) > 0
                    assert abs(i) <= num_vars
                    variables.add(abs(i))
                clauses.append(clause)
    if warnings:
        if num_vars != len(variables):
            print(f"Warning: expected {num_vars} variables but found {len(variables)}")
            # print(set(range(1, num_vars + 1)).difference(variables))
        if num_clauses != len(clauses):
            print(f"Warning: expected {num_clauses} clauses but found {len(clauses)}")

    return CNF(clauses, num_vars, var_names)
