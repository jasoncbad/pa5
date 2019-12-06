/* --------------------------------

  FindComponents.c | PA5
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Client Module for pa5

-----------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "string.h"


int main(int argc, char** argv) {
  // 1) Check that there are two command line arguments (other than the program
  // name). Quit with a usage message to stderr if more than or less than
  // two strings are given on the command line.
  printf("You entered %d arguments...\n" , argc);

  for (int i = 0; i < argc; ++i)
    printf("%s ", argv[i]);

  if (argc != 3) {
    fprintf(stderr, "%s", "STDERR: bad argument structure\n");
    exit(1);
  }

  // declare files
  FILE* inFile;
  FILE* outFile;

  // open streams to files
  inFile = fopen(argv[1], "r");
  outFile = fopen(argv[2],"w");

  int degree;
  int u, v;

  // read the first line... create a graph of that degree..
  fscanf(inFile, "%d\n", &degree);


  // create the graph..
  printf("\nCreating graph of degree %d..\n", degree);
  Graph G = newGraph(degree);

  // read the next lines and stop reading when the two reads are 0 and 0
  while(1) {
    fscanf(inFile, "%d %d\n", &u, &v);
    if (u == 0 && v == 0) {
        break;
    } else {
      addArc(G, u, v);
    }
  }

  // show the created graph:
  fprintf(outFile, "Adjacency list representation of G:\n");
  printGraph(outFile, G);
  fprintf(outFile, "\n");

  // RUN DFS on G and G^T ..
  List vertexOrder = newList();
  for (int i = 1; i <= getOrder(G); i++) {
    append(vertexOrder, i);
  }

  // FIRST CALL TO DFS
  DFS(G, vertexOrder);

  // SECOND CALL TO DFS
  Graph Gt = transpose(G);
  DFS(Gt, vertexOrder);

  // Determine the strong components of G ..
  fprintf(outFile, "G contains %d strongly connected components:\n", getStrongComponents(Gt));

  // print those stronk components
  // now find the number of strongly connected components

  // print the strong components
  List topSort = getTopologicalSort(Gt);
  moveFront(topSort);
  int root = -1;
  for (int i = 1; i <= getStrongComponents(Gt); i++) {
    fprintf(outFile, "Component %d: ", i);

    // move back
    moveBack(topSort);
    int counter = i;

    while(index(topSort) != -1) {
      if (getParent(Gt, get(topSort)) == 0) {
        counter--;
      } else {
        movePrev(topSort);
        continue;
      }

      if (counter == 0) {
        root = get(topSort);
        // weve reached the desired grouping
        while(index(topSort) != -1 && isDescendant(Gt, get(topSort), root)) {
          // print the element and move next
          fprintf(outFile, "%d ", get(topSort));
          moveNext(topSort);
        }
        break;
      } else {
        movePrev(topSort);
      }
    }
    fprintf(outFile, "\n");
  }

  // houskeeping
  fclose(inFile);
  fclose(outFile);

  freeGraph(&G);
  G = NULL;
  freeGraph(&Gt);
  Gt = NULL;

  return 0;
}
