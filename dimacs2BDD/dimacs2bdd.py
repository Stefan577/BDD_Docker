import subprocess
import os
import sys
from dimagic.dimagic import main as dimagic_main
from Logic2BDD.pylogic2bdd import main as pylogic2bdd_main


def convert_dimacs_to_bdd(input_dimacs, output_folder):
    # Erster Schritt: dimagic ausführen
    # subprocess.run(['python3.11', '../dimagic/dimagic.py', input_dimacs, '-rv', '-rc', '-l2b', '-o', output_folder])
    sys.argv = ['dimagic.py', input_dimacs, '-rv', '-rc', '-l2b', '-o', output_folder]
    dimagic_main()


    # Extrahiere Name und Ordner für pylogic2bdd
    name = os.path.splitext(os.path.basename(input_dimacs))[0]
    folder = os.path.basename(os.path.dirname(input_dimacs))

    # Setze die Argumente für pylogic2bdd und führe die Hauptfunktion aus
    sys.argv = ['pylogic2bdd.py', f"{output_folder}/{folder}", name]
    pylogic2bdd_main()

# Beispielaufruf der Funktion
#convert_dimacs_to_bdd("/home/jahns/BDD_Docker/test_data/Mendonca2009.dimacs", "output")
