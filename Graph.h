/* --------------------------------

  Graph.h | PA5
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Header File for the Graph ADT

-----------------------------------
*/
#define INF -1
#define NIL 0
#define UNDEF -2
#include "List.h"

typedef struct GraphObj* Graph;

/** construction/destruction **/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/** Access Functions **/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/** Added Accessors for PA5 **/
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
List getTopologicalSort(Graph G);
int getStrongComponents(Graph G);

/** Manipulation procedures **/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/** Added Manipulation procedures for PA5 **/
void DFS(Graph G, List S);

/** Other Operations **/
void printGraph(FILE* out, Graph G);

/** Other Operations added for PA5 **/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
int isDescendant(Graph G, int x, int y);
