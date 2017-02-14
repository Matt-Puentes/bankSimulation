CFLAGS = -g -Wall

qSim: main.o Event.o tellerLine.o
	g++ $(CFLAGS) main.o Event.o tellerLine.o -lm -o qSim

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

Event.o: Event.h Event.cpp
	g++ $(CFLAGS) -c Event.cpp

tellerLine.o: tellerLine.h tellerLine.cpp
	g++ $(CFLAGS) -c tellerLine.cpp

clean:
	rm -f main.o Event.o tellerLine.o qSim
	
all: qSim