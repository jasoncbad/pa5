# --------------------------------
#
#  Makefile | PA4
#  Programmer: Jay Montoya
#  UCSC ID: jaanmont | 1742317
#
#-----------------------------------
all : FindPath

FindPath : FindPath.o Graph.o List.o
	gcc -o FindPath FindPath.o Graph.o List.o

ListTest : ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

GraphTest : GraphTest.o Graph.o List.o
	gcc -o GraphTest GraphTest.o Graph.o List.o

GraphTest.o : GraphTest.c Graph.h
	gcc -c -std=c99 -Wall GraphTest.c

Graph.o : Graph.c Graph.h
	gcc -c -std=c99 -Wall Graph.c

FindPath.o : FindPath.c Graph.h
	gcc -c -std=c99 -Wall FindPath.c

clean :
	rm -f *.o FindPath ListTest GraphTest
