/* --------------------------------

  GraphTest.c | PA4
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Test client for Graph ADT for pa4.

-----------------------------------
*/
#include <stdio.h>
#include "Graph.h"

// main
int main(int argc, char* argv[]) {

  printf("Test client started..\n");

  // create a graph with 1 vertice
  printf("Creating new graph...\n");
  Graph G = newGraph(6);

  // add some vertices..
  printf("Adding 9 edges to this graph..\n");
  addEdge(G,2,1);
  addEdge(G,3,2);
  addEdge(G,3,1);
  addEdge(G,6,2);
  addEdge(G,6,3);
  //addEdge(G,4,3);
  //addEdge(G,6,4);
  addEdge(G,5,3);
  addEdge(G,6,5);

  printf("Running BFS on this graph with 6 as the source\n");
  BFS(G, 6);

  List result = newList();
  getPath(result, G, 4);

  fprintf(stdout, "The distance from %d to %d is %d\n", 6, 4, getDist(G, 4));
  fprintf(stdout, "A shortest %d-%d path is: ", 6,4);
  printList(stdout, result);
  fprintf(stdout, "\n");


  // print the graph contents
  printf("\nGraphAdjacency list representation:\n");
  printGraph(stdout, G);
  printf("\n");

  // use makeNukll
  printf("\nTesting makeNull()...\n");
  makeNull(G);

  // print the graph contents
  printf("\nGraphAdjacency list representation:\n");
  printGraph(stdout, G);
  printf("\n");

  // add a single directed edge
  printf("\nAdding a single directed edge from 2 to 5");
  addArc(G,2,5);

  // print the graph contents
  printf("\nGraphAdjacency list representation:\n");
  printGraph(stdout, G);
  printf("\n");


  // free the graph
  freeGraph(&G);

  G = NULL;

  printf("Test client finished..\n");
  return 0;
}
