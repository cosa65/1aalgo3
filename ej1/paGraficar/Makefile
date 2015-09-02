CC = g++
CFLAGS = -std=c++11 -o
EFLAGS = -g

BINARIES = mejorCaso peorCaso random run

all: $(BINARIES)

mejorCaso:

	@python src/casos.py $(ciudades) $(ciudades) mejorCaso.in

peorCaso:

	@python src/casos.py 1 $(ciudades) peorCaso.in

random:

	@g++ src/random.cpp -o random
	@./random random.in 1 $(ciudades) $(length)
	@rm -f random

run:

	@g++ src/ej1Timed.cpp -o timed	
	@./timed random.in times/randomT.txt
	@./timed mejorCaso.in times/mejorCasoT.txt
	@./timed peorCaso.in times/peorCasoT.txt

clean:
	@rm -f timed
	@rm -f *.in
	@rm -f *.txt