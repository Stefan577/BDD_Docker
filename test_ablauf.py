import subprocess
import os
import sys
from Logic2BDD.pylogic2bdd import main as pylogic2bdd_main

INPUT = "/home/jahns/BDD_Docker/test_data/Mendonca2009.dimacs"
OUTPUT = "output"

subprocess.run(['python3.11', 'dimagic/dimagic.py', INPUT, '-rv', '-rc', '-l2b', '-o', OUTPUT])

name = os.path.splitext(os.path.basename(INPUT))[0]
folder = os.path.basename(os.path.dirname(INPUT))


sys.argv = ['pylogic2bdd.py', f"{OUTPUT}/{folder}", name]
pylogic2bdd_main()