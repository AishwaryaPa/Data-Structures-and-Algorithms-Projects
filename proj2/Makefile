driver2: Sally.o
	g++ -g Sally.o driver2.cpp -o driver2

Sally.o: Sally.h Sally.cpp
	g++ -g -c Sally.cpp

clean:
	rm *.o
	rm *~

run:
	./driver2
