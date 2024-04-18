CC = clang
CFLAGS = -Wall -Wextra -g

all: chaine SVGwriter reseau hachage arbre SVGwriter TestChaine TestArbreQuat main Struct_File graphe TestGraphe

chaine: Chaine.c Chaine.h 
	$(CC) $(CFLAGS) -c Chaine.c -o chaine.o 

SVGwriter: SVGwriter.c SVGwriter.h chaine
	$(CC) $(CFLAGS) -c SVGwriter.c -o SVGwriter.o

reseau: Reseau.c Reseau.h chaine
	$(CC) $(CFLAGS) -c Reseau.c -o reseau.o

hachage: Hachage.c Hachage.h reseau
	$(CC) $(CFLAGS) -c Hachage.c -o hachage.o

arbre: ArbreQuat.c ArbreQuat.h reseau chaine
	$(CC) $(CFLAGS) -c ArbreQuat.c -o ArbreQuat.o

Struct_File: Struct_File.c Struct_File.h
	$(CC) $(CFLAGS) -c Struct_File.c -o Struct_File.o

graphe: Graphe.c Graphe.h reseau Struct_File
	$(CC) $(CFLAGS) -c Graphe.c -o Graphe.o

SVGwriter: SVGwriter.c SVGwriter.h reseau
	$(CC) $(CFLAGS) -c SVGwriter.c -o SVGwriter.o

TestChaine.o: TestChaine.c
	$(CC) $(CFLAGS) -c TestChaine.c -o TestChaine.o

TestArbreQuat.o: TestArbreQuat.c
	$(CC) $(CFLAGS) -c TestArbreQuat.c -o TestArbreQuat.o

TestGraphe.o: TestGraphe.c
		$(CC) $(CFLAGS) -c TestGraphe.c -o TestGraphe.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

TestChaine: TestChaine.o chaine
	$(CC) $(CFLAGS) -o TestChaine TestChaine.o chaine.o

TestArbreQuat: TestArbreQuat.o arbre reseau chaine
	$(CC) $(CFLAGS) -o TestArbreQuat TestArbreQuat.o ArbreQuat.o reseau.o chaine.o

TestGraphe: TestGraphe.o reseau chaine hachage graphe
	$(CC) $(CFLAGS) -o TestGraphe TestGraphe.o hachage.o reseau.o chaine.o Graphe.o

main: main.o arbre reseau chaine hachage SVGwriter
	$(CC) $(CFLAGS) -o main main.o ArbreQuat.o reseau.o chaine.o hachage.o  SVGwriter.o

clean:
	rm -f *.o TestChaine TestArbreQuat main
