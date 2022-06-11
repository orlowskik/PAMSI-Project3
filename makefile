program: main.o AListGraph.o AMatrixGraph.o
	g++ AListGraph.o AMatrixGraph.o main.o 

main.o: main.cpp AListGraph.h PrioQueue.h
	g++ -c -o main.o main.cpp

AListGraph.o: AListGraph.cpp AListGraph.h
	g++ -c -o AListGraph.o AListGraph.cpp

AMatrixGraph.o: AMatrixGraph.cpp AMatrixGraph.h
	g++ -c -o AMatrixGraph.o AMatrixGraph.cpp

.PHONY: clean

clean:
	rm -f *.o