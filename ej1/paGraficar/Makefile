CC = g++
CFLAGS = -std=c++11 -o
EFLAGS = -g

BINARIES = mejorCaso peorCaso random run

all: $(BINARIES)

mejorCaso:

	@python src/casos.py 0 $(ciudades) mejorCaso.in mejor $(ciudades)*10

peorCaso:

	@g++ src/random.cpp -o random
	@./random peorCaso.in 1 $(ciudades) $(ciudades)*1000 peor
	@rm -f random

random:

	@g++ src/random.cpp -o random
	@./random random.in 1 $(ciudades) $(ciudades)*1000 random
	@rm -f random

run:

	@g++ src/ej1Timed.cpp -o timed	
	@./timed mejorCaso.in times/mejorCasoT.txt
	@./timed peorCaso.in times/peorCasoT.txt
	@./timed random.in times/randomT.txt

clean:
	@rm -f timed
	@rm -f *.in
	@rm -f *.txt
	@rm -f *.o
