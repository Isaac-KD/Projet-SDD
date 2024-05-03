# Utiliser une image de base officielle Ubuntu
FROM ubuntu:latest

# Installer gcc et autres dépendances nécessaires
RUN apt-get update && apt-get install -y \
    build-essential \
    valgrind

# Copier les fichiers du répertoire src dans le conteneur
COPY src/ /app/src/

# Copier les fichiers du répertoire tests dans le conteneur
COPY tests/ /app/tests/

# Copier les fichiers du répertoire include dans le conteneur
COPY include/ /app/include/

# Copier le répertoire courant dans le conteneur
COPY . /app

# Définir le répertoire de travail
WORKDIR /app

# Compiler les fichiers sources en fichiers objets

# Compiler le programme, en ajustant les chemins selon la nouvelle structure
RUN gcc -o TestChaine tests/TestChaine.c src/Chaine.c src/SVGwriter.c -lm
RUN gcc -o TestArbreQuat tests/TestArbreQuat.c src/ArbreQuat.c src/Reseau.c src/Chaine.c src/Graphe.c src/Struct_File.c src/SVGwriter.c -lm

# Définir la commande par défaut pour exécuter le programme avec Valgrind
CMD ["valgrind", "--leak-check=full", "./TestChaine"]

#  docker build -t nom_image .
#   docker run --name nom_conteneur nom_image
#   docker stop nom_conteneur
#    docker rm nom_conteneur