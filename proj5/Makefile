test5: HashTable.o
	g++ -g HashTable.o test5.cpp -o test5

HashTable.o: HashTable.h HashTable.cpp
	g++ -g -c HashTable.cpp

clean:
	rm *.o
	rm *~

run:
	./test5
