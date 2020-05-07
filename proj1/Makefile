Driver: Graph.o 
	g++ -g Graph.o Driver.cpp -o Driver

Graph.o: Graph.h Graph.cpp
	g++ -g -c Graph.cpp

clean:
	rm *.o
	rm *~

run:
	./Driver
