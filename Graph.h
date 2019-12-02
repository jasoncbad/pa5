/* --------------------------------

  Graph.h | PA4
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

-----------------------------------
*/
#define INF -1
#define NIL 0
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

/** Manipulation procedures **/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/** Other Operations **/
void printGraph(FILE* out, Graph G);
