.c.o:   $*.h
	gcc -c $*.c

.cpp.o:	$*.h
	g++	-c $*.cpp

all: main

main:  main.o Domino.o ListaSimplesmenteEncadeada.o Pilha.o
	gcc -o $@ $^

clean:
	rm *.o *.*~ *~ main
