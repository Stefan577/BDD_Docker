import docker
import os
import argparse
import sys

DOCKER_IMAGE = "sjahns/bdd_docker"


# Funktion zum Überprüfen, ob eine Datei existiert und die richtige Endung hat
def check_file(file_path, valid_extensions):
    if not os.path.exists(file_path):
        print(f"Error: Datei '{file_path}' wurde nicht gefunden.")
        sys.exit(1)

    if not file_path.endswith(valid_extensions):
        print(f"Error: Datei '{file_path}' hat keine der erlaubten Endungen: {valid_extensions}")
        sys.exit(1)

    print(f"Datei '{file_path}' ist gültig.")


# Funktion zum Überprüfen, ob das Docker-Image lokal vorhanden ist
def check_docker_image(client):
    try:
        client.images.get(DOCKER_IMAGE)
        print(f"Docker-Image '{DOCKER_IMAGE}' ist bereits lokal vorhanden.")
    except docker.errors.ImageNotFound:
        print(f"Docker-Image '{DOCKER_IMAGE}' nicht gefunden. Es wird heruntergeladen.")
        try:
            client.images.pull(DOCKER_IMAGE)
            print(f"Docker-Image '{DOCKER_IMAGE}' wurde erfolgreich heruntergeladen.")
        except Exception as e:
            print(f"Error beim Herunterladen des Docker-Images: {str(e)}")
            sys.exit(1)


# Hauptfunktion
def main():
    # Argument-Parser erstellen
    parser = argparse.ArgumentParser(description="Skript zum Ausführen von BDDSampler in einem Docker-Container.")

    # Übergabeparameter definieren
    parser.add_argument("samples", help="Number of samples")
    parser.add_argument("bdd_path", help="Path to BDD (in dddmp format)")

    # Argumente parsen
    args = parser.parse_args()

    # Eingabedatei überprüfen
    check_file(args.bdd_path, valid_extensions=".dddmp")

    # Docker-Client initialisieren
    client = docker.from_env()

    # Überprüfen, ob das Docker-Image lokal vorhanden ist
    check_docker_image(client)

    abs_folder_path = os.path.abspath(os.path.dirname(args.bdd_path))


    # Starte den Docker-Container
    container = client.containers.run(
        image=DOCKER_IMAGE,  # Name des Docker-Images
        volumes={f"{abs_folder_path}":{'bind': '/mnt/data', 'mode': 'rw'}},
        command="/bin/bash",  # Starte eine Bash-Shell
        detach=True,  # Container im Hintergrund laufen lassen
        tty=True  # Erstelle ein Terminal
    )

    # Datei in den Docker-Container kopieren
    bdd_name = os.path.basename(args.bdd_path)

    # BDD_Docker ausführen
    command = f"/bin/bash -c 'cd /app/BDDSampler/bin && export LD_LIBRARY_PATH=/app/BDDSampler/lib:$LD_LIBRARY_PATH &&./BDDSampler -names {args.samples} /mnt/data/{bdd_name} > /mnt/data/samples.txt'"
    # command = f"/bin/bash -c 'cd /app/BDD_Docker/bin && ./BDD_Docker /mnt/data/{var_file_name} mnt/data/{exp_file_name} -suffix {name}'"
    exit_code, output = container.exec_run(command)

    # Output anzeigen
    print(f"Exit code: {exit_code}")
    print(f"Output:\n{output.decode('utf-8')}")

    # Container stoppen und entfernen
    container.stop()
    container.remove()


# Skript nur ausführen, wenn es direkt aufgerufen wird
if __name__ == "__main__":
    main()
