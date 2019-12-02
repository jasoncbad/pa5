/* --------------------------------

  List.h | PA4
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

-----------------------------------
*/
typedef struct ListObj* List;

// construction/destruction
List newList(void);
void freeList(List* pL);

// accessors
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);

// operations
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

void printList(FILE* out, List L);

// also included for this project
List copyList(List L);
void set(List L, int x);
int equals(List A, List B);
