/* --------------------------------

  FindPath.c | PA4
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Client Module for pa4

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
      addEdge(G, u, v);
    }
  }

  // show the created graph:
  printGraph(outFile, G);
  fprintf(outFile, "\n");

  List pathList = newList();
  while(1) {
    fscanf(inFile, "%d %d\n", &u, &v);
    if (u == 0 && v == 0) {
        break;
    } else {
      // perform BFS with the source being u
      BFS(G, u);
      clear(pathList);
      getPath(pathList, G, v);

      if (back(pathList) == NIL) {
        fprintf(outFile, "The distance from %d to %d is infinity\n", u, v);
        fprintf(outFile, "No %d-%d path exists\n\n", u,v);
      } else {
        fprintf(outFile, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
        fprintf(outFile, "A shortest %d-%d path is: ", u,v);
        printList(outFile, pathList);
        fprintf(outFile, "\n");
      }
    }
  }


  // houskeeping
  fclose(inFile);
  fclose(outFile);

  freeGraph(&G);
  G = NULL;

  freeList(&pathList);
  pathList = NULL;

  return 0;
}
