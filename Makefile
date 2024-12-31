output: main.o CPU.o Interface.o
	g++ main.o CPU.o Interface.o -o output -lSDL2

main.o: main.cpp
	g++ -c main.cpp

CPU.o: CPU.cpp CPU.h
	g++ -c CPU.cpp

Interface.o: Interface.cpp Interface.h

clean:
	rm *.o output