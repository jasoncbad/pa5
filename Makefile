# --------------------------------
#
#  Makefile | PA5
#  Programmer: Jay Montoya
#  UCSC ID: jaanmont | 1742317
#
#-----------------------------------
all : FindComponents

FindComponents : FindComponents.o Graph.o List.o
	gcc -o FindComponents FindComponents.o Graph.o List.o

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

FindComponents.o : FindComponents.c Graph.h
	gcc -c -std=c99 -Wall FindComponents.c

clean :
	rm -f *.o FindComponents ListTest BigIntegerTest GraphTest
