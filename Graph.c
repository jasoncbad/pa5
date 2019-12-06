/* --------------------------------

  Graph.c | PA5
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Definitions for the Graph ADT.

-----------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define DEBUG 0


// prototype
void visit(Graph G, int* time, int u);

// definition of a GraphObj
typedef struct GraphObj {
  int order; // num vertices
  int size; // num edges
  int lastSource; // the last vertex used as the source

  List* adjacencyLists; // array of lists whose ith elements contain the
                        // neighbors of vertext i

  int* colors; // array of ints representing the color of vertex i
              // ( 0 = white, 1 = grey, 2 = black )

  int* parents; // array of ints representing the parent of vertex i

  int* distances; // array of ints whos ith element is the distance from the
                  // most recent source to vertex i.

  List topologicalSort;


  // added for PA5
  int* discoverTimes;
  int* finishTimes;

} GraphObj;

// newMatrix()
// returns a reference to a new graph with n elements and no edges
Graph newGraph(int n) {
  // allocate memory for the graph itself
  Graph G;
  G = malloc(sizeof(GraphObj));

  // initialize the array of lists..
  G->adjacencyLists = malloc(sizeof(List) * (n+1));
  for(int i = 0; i < n+1; i++) {
    G->adjacencyLists[i] = newList();
  }

  // initialize the array of ints
  G->colors = malloc(sizeof(int) * (n + 1));

  // initialize the array of ints
  G->parents = malloc(sizeof(int) * (n + 1));

  // initialize the array of ints
  G->distances = malloc(sizeof(int) * (n + 1));

  // initialize the array of ints
  G->discoverTimes = malloc(sizeof(int) * (n + 1));

  // initialize the array of ints
  G->finishTimes = malloc(sizeof(int) * (n + 1));

  // initialize the list for holding the topological sort
  G->topologicalSort = newList();


  for (int i = 0; i < n+1; i++) {
    G->distances[i] = INF;
    G->parents[i] = NIL;
    G->discoverTimes[i] = UNDEF;
    G->finishTimes[i] = UNDEF;
  }

  // initialize remaining values..
  G->order = n;
  G->size = 0;
  G->lastSource = NIL;

  return G;
}

// freeGraph()
// frees all dynamic memory pertaining to the Graph pointer pG
void freeGraph(Graph* pG) {
  if (pG != NULL && *pG != NULL) {

    // free the adjacency Lists
    for (int i = 0; i < (*pG)->order + 1; i++) {
      freeList(&((*pG)->adjacencyLists[i]));
    }
    freeList(&((*pG)->topologicalSort));
    free((*pG)->adjacencyLists);
    free((*pG)->colors);
    free((*pG)->parents);
    free((*pG)->distances);
    free((*pG)->discoverTimes);
    free((*pG)->finishTimes);

    (*pG)->topologicalSort = NULL;
    (*pG)->adjacencyLists = NULL;
    (*pG)->colors = NULL;
    (*pG)->parents = NULL;
    (*pG)->distances = NULL;
    (*pG)->discoverTimes = NULL;
    (*pG)->finishTimes = NULL;

    free((*pG));
    *pG = NULL;
  }
}

// -----------------------------------------------------------------
// access functions
// -----------------------------------------------------------------

// getOrder()
// returns the order (number of vertices) for this graph G.
int getOrder(Graph G) {
  return G->order;
}

// getSize()
// returns the size (number of edges) for this graph G.
int getSize(Graph G) {
    return G->size;
}

// getSource()
// returns the most recently used source value
int getSource(Graph G) {
  return G->lastSource;
}

// getParent()
// returns the parent of the given vertice 'u'.
// PRE: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
  if (((getOrder(G) >= u )&&( u >= 1))) {
    return (G->parents)[u];
  } else {
    return NIL;
  }
}

// getDistance()
// returns the distance of the path s-u where 's' is the source
// and 'u' is the given parameter
// PRE: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
  if (u >= 1 && u <= getOrder(G)) {
    return (G->distances)[u];
  }
  return 0;
}

// getPath()
// appends to List L the path from s to u
// PRE: 1 <= u <= getOrder(G) and getSource(G) != NIL
void getPath(List L, Graph G, int u) {
  if ((u >= 1 && u <= getOrder(G)) && (getSource(G) != NIL)) {

    if (getDist(G,u) == INF) {
        append(L, NIL);
        return;
    }

    int x = u;
    append(L, x);
    moveBack(L);
    for (int i = 0; i < getDist(G,u); i++) {
      x = getParent(G, x);
      insertBefore(L, x);
      movePrev(L);
    }

  } else {
      printf("\tgetPath() -- precondition failed to pass! nothing done in this call");
      return;
  }
}

// getDiscover()
// returns the discover time for this particular vertex
// after DFS is run..
// PRE:  1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u) {
  if ((u >= 1 && u <= getOrder(G)) && (getSource(G) != NIL)) {
    printf("\n\tgetDiscover(%d) --> %d", u, G->discoverTimes[u]);

    // get the discover time from the discoverTimes array
    return G->discoverTimes[u];
  } else {
    //printf("\tgetDiscover() -- precondition failed to pass! nothing done in this call");
    return UNDEF;
  }
}

// getFinish()
// returns the finish time for this particular vertex
// after DFS is run
int getFinish(Graph G, int u) {
  if ((u >= 1 && u <= getOrder(G)) && (getSource(G) != NIL)) {
    // get the finish time from the finishTimes array
    return G->finishTimes[u];
  } else {

    //printf("\tgetFinish() -- precondition failed to pass! nothing done in this call");
    return UNDEF;
  }
}

// getTopologicalSort()
// retrieves the topological sort of vertices after DFS is run
List getTopologicalSort(Graph G) {
  return G->topologicalSort;
}

// getStrongComponents()
// retrieves the number of strongly connected components in G..
int getStrongComponents(Graph G) {
  int x = 0;

  // count the number of vertices with parent[x] = 0 ..
  // by definition of an individual tree root
  for (int i = 1; i <= getOrder(G); i++) {
    if (G->parents[i] == 0) {
      x++;
    }
  }
  return x;
}


// -----------------------------------------------------------------
// manipulation procedures
// -----------------------------------------------------------------

// makeNull()
// deletes all edges in the graph, making the null graph
void makeNull(Graph G) {
  for (int i = 0; i <= getOrder(G); i++) {
    clear(G->adjacencyLists[i]);
  }
  G->size = 0;
}

// addEdge()
// adds an undirected edge between u and v.
void addEdge(Graph G, int u, int v) {
  // in other words, adds u to v's adjacency list, and adds v to u's
  // adjacency list
  // first check the precondition
  if ((u >= 1 && u <= getOrder(G)) && (v >= 1 && v <= getOrder(G))) {
    // some variables we will need..
    List U = (G->adjacencyLists)[u];
    List V = (G->adjacencyLists)[v];

    //printf("List U size: %d\n", length(U));
    //printf("List V size: %d\n\n", length(V));

    // add u to v's adjacency list
    // this requires inserting u into the correct position..
    moveFront(V);
    if (index(V) == -1) {
      append(V, u);
      //printf("\t\tappended u to the V list\n");
    } else {
      // try each position
      while(index(V) != -1) {
        if (u < get(V)) {
          insertBefore(V, u);
          //printf("\t\tinserted u before cursor in the V list\n");
          break;
        } else {
          moveNext(V);
        }
      }
      // by this point u might still have not been inserted at the back
      if (back(V) < u ) {
        append(V, u);
        //printf("\t\tappended u to the V list (end case)\n");
      }
    }

    // do the same thing but with v to u
    moveFront(U);
    if (index(U) == -1) {
      append(U, v);
      //printf("\t\tappended v to the U list\n");
    } else {
      // try each position
      while(index(U) != -1) {
        if (v < get(U)) {
          insertBefore(U, v);
          //printf("\t\tinserted v before cursor in the U list\n");
          break;
        } else {
          moveNext(U);
        }
      }
      // by this point u might still have not been inserted at the back
      if (back(U) < v ) {
        append(U, v);
        //printf("\t\tappended v to the U list (end case)\n");
      }
    }
    G->size = getSize(G) + 1;
    return;
  } else {
      printf("\taddEdge() -- precondition failed to pass! nothing done in this call");
      return;
  }
}

// addArc()
// adds a directed edge from u to v.
void addArc(Graph G, int u, int v) {
  // in other words, adds u to v's adjacency list, and adds v to u's
  // adjacency list
  // some variables we will need..
  List U = (G->adjacencyLists)[u];

  // first check the precondition
  if ((u >= 1 && u <= getOrder(G)) && (v >= 1 && v <= getOrder(G))) {
    // do the same thing but with v to u
    moveFront(U);
    if (index(U) == -1) {
      append(U, v);
      //printf("\t\tappended v to the U list\n");
    } else {
      // try each position
      while(index(U) != -1) {
        if (v < get(U)) {
          insertBefore(U, v);
          //printf("\t\tinserted v before cursor in the U list\n");
          break;
        } else {
          moveNext(U);
        }
      }
      // by this point u might still have not been inserted at the back
      if (back(U) < v ) {
        append(U, v);
        //printf("\t\tappended v to the U list (end case)\n");
      }
    }
    G->size++;
  } else {
    printf("\taddEdge() -- precondition failed to pass! nothing done in this call");
    return;
  }
}

// BFS()
// runs BFS on the graph
void BFS(Graph G, int s) {
  //BFS is going to modify the following components:
  //  1. LastSource
  //  2. Colors
  //  3. Parents
  //  4. Distances
  G->lastSource = s;

  // initialize propertis of all x where x is in V(G) - {s}
  for (int i = 0; i <= getOrder(G); i++) {
    if (i == s) continue; // except s

    *((G->colors) + i) =  0; // 0 = white
    *((G->distances) + i) = INF;
    *((G->parents) + i) = NIL;
  }

  // now initialize the source vertex
  (G->colors)[s] = 1; // s = GRAY
  (G->distances)[s] = 0;
  (G->parents)[s] = NIL;



  // create a list to represent the queue
  List queue = newList();

  // Enqueue(s)
  append(queue, s);

  // BFS main loop
  while (length(queue) != 0) {
    int u = front(queue); deleteFront(queue); // got to delete it too

    List adjacencyList = (G->adjacencyLists)[u];

    moveFront(adjacencyList);
    while(index(adjacencyList) != -1) {
      if ((G->colors)[get(adjacencyList)] == 0) { // if colors[v] = white

        (G->colors)[get(adjacencyList)] = 1; // colors[v] = gray

        (G->distances)[get(adjacencyList)] = (G->distances)[u] + 1;

        (G->parents)[get(adjacencyList)] = u;

        append(queue, get(adjacencyList));
      }

      moveNext(adjacencyList);
    }

    (G->colors)[u] = 2;


  }

  // print out everything:
  /*for (int i = 1; i <= getOrder(G); i++) {
    printf("%d:\t\tPARENT: %d \t\tDISTANCE: %d\t\tCOLOR: %d\n", i, G->parents[i], G->distances[i], G->colors[i]);
  }
  printf("\n");*/

  // houskeeping
  freeList(&queue);
  queue = NULL;
}

// DFS()
// performs the DFS algorithm on the given graph object
void DFS(Graph G, List S) {
  clear(G->topologicalSort);

  // for each vertex in the graph
  for (int i = 1; i <= getOrder(G); i++) {
    // set the color to white and the parent to nil
    G->colors[i] = 0;
    G->parents[i] = NIL;
  }

  // time set to 0
  int time;

  int* timePtr = &time;
  *timePtr = 0;

  // refer to the list for the order of processing vertices
  moveFront(S);
  while(index(S) != -1) {
    if (G->colors[get(S)] == 0) {
      visit(G, timePtr, get(S));
    }

    moveNext(S);
  }

  timePtr = NULL;

  // clear the given list and rebuild it by order of decreasing finish times
  // The Graph's order gives the number of vertices
  // and by PA specification the last finish time is equal to 2 * |V|.
  clear(S);
  for (int i = 1; i <= getOrder(G) ; i++) {
     if (i == 1) { // for the first vertice just add it so we have a comparison
       append(S, i);
       continue;
     }

     moveFront(S);      // move cursor to front
     int inserted = 0;  // flag indicating a successful insert


     while(index(S) != -1) {

       // compare the finish time.. insert before if it comes before
       // the finish time of the cursor.. then break the while loop
       if (G->finishTimes[i] > G->finishTimes[get(S)]) {
         insertBefore(S, i);
         inserted = 1;
         break;
       }
       moveNext(S);
     }
     // if the while loop runs dead.. check the inserted flag and append
     if (inserted == 0) {
       append(S, i);
     }
  }
} // end of DFS

// visit()
// helper function used in hand with DFS
void visit(Graph G, int* time, int u) {
  G->colors[u] = 1; // color[u] = GRAY

  *time = *time + 1;

  G->discoverTimes[u] = *time;

  List adjacencyList = G->adjacencyLists[u];
  moveFront(adjacencyList);
  while(index(adjacencyList) != -1) { // for each v adjacent to u
    if (G->colors[get(adjacencyList)] == 0) {
        // parent[v] = u
        G->parents[get(adjacencyList)] = u;

        // and now visit
        visit(G, time, get(adjacencyList));
    }

    moveNext(adjacencyList);
  }

  // color[u] = black
  G->colors[u] = 2;
  prepend(G->topologicalSort, u);
  G->finishTimes[u] = *time  = *time + 1;
}

// -----------------------------------------------------------------
// other operations
// -----------------------------------------------------------------

// isDescendant()
// determines whether x is some isDescendant of y.
int isDescendant(Graph G, int x, int y) {
  int cursor = x;
  while(cursor != y) {
      if (cursor == 0) {
        return 0;
      }
      cursor = getParent(G, cursor);
  }
  return 1;
}

// printGraph()
// prints graph to the filestream indicated by out.
void printGraph(FILE* out, Graph G) {
  for (int i = 0 ; i < getOrder(G); i++) {
    fprintf(out, "%d: ", (i+1));
    printList(out, (G->adjacencyLists)[i+1]);
  }

  if (DEBUG) {
    fprintf(stdout, "\n");
    for (int i = 1; i <= getOrder(G); i++) {
      fprintf(stdout, "%d:\tdiscover:%d\tfinish:%d\tparent:%d\n", i, G->discoverTimes[i], G->finishTimes[i], G->parents[i]);
    }
  }
}

// transpose()
// returns the transpose of graph G as a new graph
Graph transpose(Graph G) {
  // create the new graph to return
  Graph X = newGraph(getOrder(G));

  // we need to copy all fields
  // order was already constructed by call to newGraph
  X->size = getSize(G);
  X->lastSource = getSource(G);

  // now start building the adjacency lists:
  for (int i = 1; i <= getOrder(G); i++) {
    List GList = G->adjacencyLists[i];

    // main loop of building the adjacency list
    moveFront(GList);
    while (index(GList) != -1) {
      insertSorted(X->adjacencyLists[get(GList)], i);
      moveNext(GList);
    }

    // copy over other values too
    X->colors[i] = G->colors[i];
    X->parents[i] = G->parents[i];
    X->distances[i] = G->distances[i];
    X->discoverTimes[i] = G->discoverTimes[i];
    X->finishTimes[i] = G->finishTimes[i];
  }

  return X;
}

// copyGraph()
// returns a deep copy of graph G as a new Graph object
Graph copyGraph(Graph G) {
   Graph X = newGraph(getOrder(G));

   // we need to copy all fields
   // order was already constructed by call to newGraph
   X->size = getSize(G);
   X->lastSource = getSource(G);

   // now start building the adjacency lists:
   for (int i = 1; i <= getOrder(G); i++) {

     // take care of the list
     freeList(&(X->adjacencyLists[i]));
     X->adjacencyLists[i] = copyList(G->adjacencyLists[i]);

     // copy over other values too
     X->colors[i] = G->colors[i];
     X->parents[i] = G->parents[i];
     X->distances[i] = G->distances[i];
     X->discoverTimes[i] = G->discoverTimes[i];
     X->finishTimes[i] = G->finishTimes[i];
   }
   return X;
}
