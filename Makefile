CC = g++
CFLAGS = -std=c++11 -o
EFLAGS = -g

BINARIES = ej3

.PHONY: ej1 ej2 ej3

all: $(BINARIES)

debug1: ej1/ej1.cpp
	$(CC) ej1/ej1.cpp $(EFLAGS) $(CFLAGS) exj1	

ej1: ej1/ej1.cpp
	$(CC) ej1/ej1.cpp $(CFLAGS) exj1

ej2: ej2/mediana.cpp
	$(CC) ej2/mediana.cpp $(CFLAGS) exj2

ej3: ej3/ej3.cpp
	$(CC) ej3/ej3.cpp $(CFLAGS) exj3

ronda: ej3/ronda.h
	$(CC) ej3/ronda.h $(CFLAGS) ronda 

clean:
	rm -f ej1/*.o exj1
	rm -f ej2/*.o exj2
	rm -f ej3/*.o exj3
