CC = gcc
CFLAGS = -Wall -Wextra -g

all: chaine SVGwriter reseau hachage arbre SVGwriter TestChaine TestArbreQuat main Struct_File graphe TestGraphe TestReseau MesurePerformance ChaineMain ReconstitueReseau TestHachage

SVGwriter: src/SVGwriter.c include/SVGwriter.h 
	$(CC) $(CFLAGS) -c src/SVGwriter.c -o SVGwriter.o
	
chaine: src/Chaine.c include/Chaine.h SVGwriter
	$(CC) $(CFLAGS) -c src/Chaine.c -o chaine.o

reseau: src/Reseau.c include/Reseau.h chaine
	$(CC) $(CFLAGS) -c src/Reseau.c -o reseau.o

hachage: src/Hachage.c include/Hachage.h reseau
	$(CC) $(CFLAGS) -c src/Hachage.c -o hachage.o

arbre: src/ArbreQuat.c include/ArbreQuat.h reseau chaine
	$(CC) $(CFLAGS) -c src/ArbreQuat.c -o ArbreQuat.o

Struct_File: src/Struct_File.c include/Struct_File.h
	$(CC) $(CFLAGS) -c src/Struct_File.c -o Struct_File.o

graphe: src/Graphe.c include/Graphe.h reseau Struct_File
	$(CC) $(CFLAGS) -c src/Graphe.c -o Graphe.o

TestChaine.o: tests/TestChaine.c
	$(CC) $(CFLAGS) -c tests/TestChaine.c -o TestChaine.o

TestArbreQuat.o: tests/TestArbreQuat.c
	$(CC) $(CFLAGS) -c tests/TestArbreQuat.c -o TestArbreQuat.o

TestGraphe.o: tests/TestGraphe.c
	$(CC) $(CFLAGS) -c tests/TestGraphe.c -o TestGraphe.o

TestReseau.o: tests/TestReseau.c
	$(CC) $(CFLAGS) -c tests/TestReseau.c -o TestReseau.o

TestHachage.o: tests/TestHachage.c
	$(CC) $(CFLAGS) -c tests/TestHachage.c -o TestHachage.o

MesurePerformance.o: src/MesurePerformance.c
	$(CC) $(CFLAGS) -c src/MesurePerformance.c -o MesurePerformance.o

ReconstitueReseau.o: src/ReconstitueReseau.c
	$(CC) $(CFLAGS) -c src/ReconstitueReseau.c -o ReconstitueReseau.o

ChaineMain.o: src/ChaineMain.c
	$(CC) $(CFLAGS) -c src/ChaineMain.c -o ChaineMain.o

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

TestChaine: TestChaine.o chaine
	$(CC) $(CFLAGS) -o TestChaine TestChaine.o chaine.o SVGwriter.o

TestArbreQuat: TestArbreQuat.o arbre reseau chaine
	$(CC) $(CFLAGS) -o TestArbreQuat TestArbreQuat.o ArbreQuat.o reseau.o chaine.o SVGwriter.o

TestGraphe: TestGraphe.o reseau chaine hachage graphe
	$(CC) $(CFLAGS) -o TestGraphe TestGraphe.o hachage.o reseau.o chaine.o Graphe.o Struct_File.o SVGwriter.o

TestReseau: TestReseau.o reseau chaine 
	$(CC) $(CFLAGS) -o TestReseau TestReseau.o reseau.o chaine.o SVGwriter.o

TestHachage: TestHachage.o reseau chaine hachage
	$(CC) $(CFLAGS) -o TestHachage TestHachage.o reseau.o chaine.o SVGwriter.o hachage.o 

MesurePerformance: MesurePerformance.o reseau arbre hachage
	$(CC) $(CFLAGS) -o MesurePerformance MesurePerformance.o reseau.o chaine.o hachage.o ArbreQuat.o SVGwriter.o

ReconstitueReseau: ReconstitueReseau.o reseau arbre hachage chaine SVGwriter
	$(CC) $(CFLAGS) -o ReconstitueReseau ReconstitueReseau.o reseau.o ArbreQuat.o chaine.o hachage.o SVGwriter.o

ChaineMain: ChaineMain.o chaine
	$(CC) $(CFLAGS) -o ChaineMain ChaineMain.o chaine.o SVGwriter.o

main: main.o arbre reseau chaine hachage SVGwriter
	$(CC) $(CFLAGS) -o main main.o ArbreQuat.o reseau.o chaine.o hachage.o SVGwriter.o

clean:
	rm -f *.o TestChaine TestArbreQuat TestGraphe main MesurePerformance TestReseau tmp tmpAleatoire ChaineMain SVGwriter ReconstitueReseau TestHachage

cleanDoc:
	rm -f exo1.3.html reconstitueReseauArbre.html reconstitueReseauHachage.html reconstitueReseauListe.html
