import os
import sys
from dimacs2BDD.dimagic import main as dimagic_main
from dimacs2BDD.pylogic2bdd import main as pylogic2bdd_main
from dimacs2BDD.pysampleBDD import main as pysample_bdd_main


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


def sample_bdd(number_samples, bdd_path):

    sys.argv = ['pysampleBDD.py', str(number_samples), bdd_path]
    pysample_bdd_main()


    sample_path = os.path.join(os.path.dirname(bdd_path), "samples.txt")
    configurations = []

    with open(sample_path, 'r') as file:
        for line in file:
            # Entferne führende/trailing Leerzeichen und spalte die Zeile in Features auf
            features = line.strip().split()

            # Leere Liste für die gefilterten Features in dieser Zeile/Konfiguration
            filtered_features = []
            skip_next = False  # Flag zum Überspringen des nächsten Elements, falls 'not' gefunden wird

            for i in range(len(features)):
                if skip_next:
                    skip_next = False
                    continue

                if features[i] == 'not' and i + 1 < len(features):
                    # Überspringe das Feature nach 'not'
                    skip_next = True
                else:
                    # Füge das Feature hinzu, wenn es nicht mit 'not' kombiniert ist
                    filtered_features.append(features[i])

            # Füge die gefilterte Liste der Features als eine Konfiguration hinzu
            configurations.append(filtered_features)
    return configurations

#Beispielauruf der Funktion
sample_bdd(10, "/home/jahns/BDD_Docker/output/test_data/Mendonca2009.dddmp")

