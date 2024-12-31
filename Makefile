output: main.o CPU.o
	g++ main.o CPU.o -o output

main.o: main.cpp
	g++ -c main.cpp

CPU.o: CPU.cpp CPU.h
	g++ -c CPU.cpp

clean:
	rm *.o output