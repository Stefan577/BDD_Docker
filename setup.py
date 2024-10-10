from setuptools import setup, find_packages

setup(
    name="pydimacs2BDD",  # Der Name des Projekts
    version="0.2",  # Versionsnummer
    packages={'dimacs2BDD'},  # Findet alle Pakete automatisch
    install_requires=["docker >= 7.1.0"],  # Abhängigkeiten, falls vorhanden
    description="A dimacs to BDD Docker project",  # Kurze Beschreibung
    author="Stefan",  # Dein Name oder Team
    url="https://github.com/Stefan577/BDD_Docker",  # URL zu deinem Projekt
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.11',  # Mindestanforderung für Python-Version
)
