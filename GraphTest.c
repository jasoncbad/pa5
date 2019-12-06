/* --------------------------------

  GraphTest.c | PA5
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

  // adding more directed edges to make things complicated
  addArc(G,2,6);
  addArc(G,2,4);
  addArc(G,1,5);
  addArc(G,1,2);
  addArc(G,1,3);
  addArc(G,3,2);
  addArc(G,4,1);
  addArc(G,5,6);
  addArc(G,6,3);
  addArc(G,6,5);

  // print the graph contents
  printf("\nGraphAdjacency list representation:\n");
  printGraph(stdout, G);
  printf("\n");


  // transpose the graph
  printf("\nTransposing this graph yields:\n");
  Graph X = transpose(G);
  printGraph(stdout, X);
  printf("\n");

  // copying this graph
  /*printf("\nCopying this graph yields:\n");
  Graph Y = copyGraph(X);
  printGraph(stdout, Y);
  printf("\n");*/


  // now we need to test DFS
  List verticesOrder = newList();
  prepend(verticesOrder, 1);
  prepend(verticesOrder, 2);
  prepend(verticesOrder, 3);
  prepend(verticesOrder, 4);
  prepend(verticesOrder, 5);
  prepend(verticesOrder, 6);

  printf("\nRunning DFS...\n\nDFS RESULTS:\n");
  DFS(G, verticesOrder);

  printGraph(stdout, G);
  printf("\n");

  printf("Vertices by order of decreasing finish times: \n");
  printList(stdout, verticesOrder);
  printf("\n");

  // calculate transpose of G.
  printf("Calculating transpose of G...\n");
  Graph Gt = transpose(G);

  // run DFS on transpose but with the new list
  printf("\nRunning DFS on Gt but with the new vertice ordering\n");
  DFS(Gt, verticesOrder);

  printf("\nResult of DFS on G transpose: \n");
  printGraph(stdout, Gt);
  printf("\n");

  // create a new graph
  printf("\nCreating a new graph...\n");
  Graph Y = newGraph(8);
  addArc(Y,1,2);
  addArc(Y,2,5);
  addArc(Y,2,6);
  addArc(Y,3,4);
  addArc(Y,4,8);
  addArc(Y,5,1);
  addArc(Y,6,5);
  addArc(Y,6,7);
  addArc(Y,7,3);
  addArc(Y,7,4);
  addArc(Y,8,7);
  printGraph(stdout, Y);
  printf("\n");

  // call DFS
  clear(verticesOrder);
  append(verticesOrder, 1);
  append(verticesOrder, 2);
  append(verticesOrder, 3);
  append(verticesOrder, 4);
  append(verticesOrder, 5);
  append(verticesOrder, 6);
  append(verticesOrder, 7);
  append(verticesOrder, 8);
  printf("\nRunning DFS...\n\nDFS RESULTS:\n");
  DFS(Y, verticesOrder);

  printGraph(stdout, Y);
  printf("\n");

  // calculate transpose of Y
  printf("Calculating transpose of Y...\n");
  Graph Yt = transpose(Y);

  // run DFS on transpose but with the new list
  printf("\nRunning DFS on Yt but with the new vertice ordering\n");
  DFS(Yt, verticesOrder);

  printf("\nResult of DFS on Y transpose: \n");
  printGraph(stdout, Yt);
  printf("\n");

  // now find the number of strongly connected components
  printf("\nY transpose contains %d strongly connected components:\n", getStrongComponents(Yt));

  // print the strong components
  List topSort = getTopologicalSort(Yt);
  moveFront(topSort);
  int root = front(topSort);
  for (int i = 1; i <= getStrongComponents(Yt); i++) {
    printf("Component %d: ", i);

    while(index(topSort) != -1) {
      if (isDescendant(Yt, get(topSort), root)) {
        printf("%d ", get(topSort));
        moveNext(topSort);
      } else {
        root = get(topSort);
        break;
      }
    }

    printf("\n");
  }
  printf("\n\n");

  // free the graph
  freeGraph(&Gt);
  freeGraph(&Yt);
  freeGraph(&G);
  freeGraph(&Y);
  freeGraph(&X);
  freeGraph(&Y);
  freeList(&result);
  freeList(&verticesOrder);

  G = NULL;
  Gt = NULL;
  verticesOrder = NULL;

  result = NULL;
  X = NULL;
  Y = NULL;

  printf("Test client finished..\n");
  return 0;
}
