CC = g++
CFLAGS = -std=c++11 -o
EFLAGS = -g

BINARIES = debug1

.PHONY: ej1 ej3

all: $(BINARIES)

debug1: ej1/ej1.cpp
	$(CC) ej1/ej1.cpp $(EFLAGS) $(CFLAGS) exj1	

ej1: ej1/ej1.cpp
	$(CC) ej1/ej1.cpp $(CFLAGS) exj1

#ej2: ej2/ej2.cpp
#	$(CC) $(CFLAGS) ej2/ej2.cpp ej2/ej2

ej3: ej3/ej3.cpp
	$(CC) $(CFLAGS) ej3/ej3.cpp exj3
	cd ej3

clean:
	rm -f ej1/*.o ej1/ej1
	rm -f ej2/*.o ej2/ej2
	rm -f ej3/*.o ej3/ej3