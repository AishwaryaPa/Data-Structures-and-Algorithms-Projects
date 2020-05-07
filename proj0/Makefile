driver.out: driver.o joke.o
	g++ -Wall -o driver.out driver.o joke.o

driver.o: driver.cpp
	g++ -Wall -ansi -c driver.cpp

joke.o: joke.cpp joke.h
	g++ -Wall -ansi -c joke.cpp

clean:
	rm -rf *.o
	rm -f *# *h.gch *~
	rm -rf *.out

run:	driver.out
	./driver
