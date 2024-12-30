output: main.o Chip8.o
	g++ main.o Chip8.o -o output

main.o: main.cpp
	g++ -c main.cpp

Chip8.o: Chip8.cpp Chip8.h
	g++ -c Chip8.cpp

clean:
	rm *.o output