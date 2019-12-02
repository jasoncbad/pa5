/* --------------------------------

  List.c | PA4
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Definitions for the list ADT.

-----------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// definition of a NodeObj
typedef struct NodeObj {

  int value;
  struct NodeObj* next; // next NodeObj
  struct NodeObj* prev; // previous

} NodeObj;

// definition of a Node type
typedef NodeObj* Node;

// definition of a ListObj
typedef struct ListObj {
  Node head;    // refers to the head node
  Node tail;    // refers to the tail node
  Node cursor;  // cursor
  int length;   // integer representing the length
  int index;
} ListObj;


// newNode()
// Returns reference to the new Node object. Initializes fields.
// Private.
Node newNode(int data) {
  Node N = malloc(sizeof(NodeObj));
   N->value = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Free's heap memory pointed to by *pN, sets *pN to NULL.
// Private
void freeNode(Node* pN) {
  if(pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }

}

// newList()
// returns reference to a new empty List object
List newList(void) {
  List L;

  // code that initializes L
  L = malloc(sizeof(ListObj));
  L->head = L->cursor = NULL; // setting the head/tail and cursor to NULL
  L->tail = NULL;
                              // since our list is empty
  L->length = 0;              // setting the length to 0
  L->cursor = NULL;
  L->index = -1;              // effectively sets the cursor index
  return (L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL) {
  if (pL != NULL && *pL!= NULL) {
    // freeing heap memory
    // I need to free all nodes in this List
    moveFront(*pL);
    while ((*pL)->length != 0) {
      deleteFront(*pL);
    }

    free(*pL);
    *pL = NULL;
  }
}

// length()
// returns the number of elements in L
int length(List L) {
  if (L == NULL) {
    //printf("List Error: attempt to call length() on NULL object");
    return 0;
  }
  return L->length;
}

// index()
// returns the index of the cursor element if defined, -1 otherwise.
int index(List L) {
  if (L->cursor == NULL) // if cursor is null return -1
    return -1;

  // else return what it is defined as
  return L->index;
}

// front()
// Returns the front element of L.
// PRE: length() > 0
int front(List L) {
  if (length(L) < 1) {
    printf("List Error: attempt to access front node when NULL\n");
  }

  return (L->head)->value;
}

// back()
// returns the back element of L
// PRE: length() > 0
int back(List L) {
  if (length(L) < 1) {
    printf("List Error: attempt to access back node when size = 0\n");
  }

  // return tail element
  return L->tail->value;
}

// prepend()
// prepends an element to the front of a list
void prepend(List L, int data) {
  // Inserts new element into L.
  // If L is non-empty, inserts it before the head node

  if (length(L) == 0) {
    // code for inserting a one and only node
    Node new_node = newNode(data);

    L->cursor = new_node; // here is where I initiate the cursor
    L->index = 0;
    L->head = new_node; // set the head/tail of the list
    L->tail = new_node;
    new_node->next = NULL; // set the node's next and prev
    new_node->prev = NULL;

    // increment list size
    (L->length)++;
    return;
  }

  // otherwise length is > 0
  // code for inserting a node BEFORE the head node
  Node new_node = newNode(data);

  new_node->next = L->head;
  new_node->prev = NULL;
  L->head->prev = new_node;
  L->head = new_node;

  // increment list size and adjust cursor
  (L->length)++;
  if (index(L) != -1) {
     (L->index)++;
  }
  return;
}

// append()
// appends an element to the back of the list
void append(List L, int data) {
  // inserts new element into L.
  // if L is non-empty, inserts it after the last element
  if (L == NULL){
    return;
  }



  if (length(L) == 0) {
    // code for inserting a one and only node
    prepend(L, data); // recycle code!
    //(L->length)--;
    return;
  }


  // otherwise length is > 0
  // code for inserting a node AFTER the last node
  Node new_node = newNode(data);
  // Node target_node = L->head;
  if (length(L) > 0){
    L->tail->next = new_node;
    new_node->prev = L->tail;
    L->tail = new_node;
  } else {
    L->head = L->tail = new_node;
  }

  // increment list size
  // no cursor redefinition needed
  (L->length)++;
  return;
}

// deleteFront()
// deletes the front element
// PRE: length >0
void deleteFront(List L) {

  Node N;

  if (length(L) == 0) {
    //printf("List Error: attempt to call deleteFront() on null list\n");
    return;
  }
  // LEFT WITH TWO CASES: length = 1 and length > 1
  if (length(L) == 1) {
    // code for deleting a front single node
    freeNode((&(L->head)));
    L->head = NULL; // checkpoint all values
    L->tail = NULL;
    L->length = 0;
    L->index = -1;
    L->cursor = NULL;
    return;
  }

  // code for freeing a front node when length > 1

  L->head = L->head->next;
  N = L->head->prev;

  //N = (Node) L->head;
  //L->head = (Node) N->next;
  N->prev = NULL;
  freeNode(&N);
  L->length--;

  // if the cursor was at the front when deleted
  if (index(L) == 0)
  {
    // set cursor undefined
    L->cursor = NULL;
    L->index = -1;
  } else if (index(L) > 0) {
    L->index--; // adjust cursor
  }
  return;
}

// deleteBack()
// deletes the backmost element in the list
void deleteBack(List L) {

  Node N = NULL;

  if (L == NULL || length(L) <= 0) {
    //printf("List Error: attempt to call deleteBack() on null list\n");
    return;
  }

  // if the cursor was at the back when deleted
  if (index(L) == (length(L) - 1))
  {
    // set cursor undefined
    L->cursor = NULL;
    L->index = -1;
  }

  // TWO CASES: length = 1 and length > 1
  if (length(L) == 1) {
    /*freeNode(&(L->head));
    //L->head = NULL;
    L->tail = NULL;
    L->length = 0;
    L->index = -1;
    L->cursor = NULL;*/
    clear(L);
  } else if (length(L) > 1) {
    // code for freeing a back node when length > 1
    N = L->tail;
    L->tail = L->tail->prev;

    L->tail->next =NULL;

    N->prev = NULL;

    freeNode(&N);
    L->length--;
  }


  // else if the cursor was anywhere else we do not need to adjust it
  // only adjust the length of the list
  return;
}


// moveFront()
// Moves the cursor to the frontmost element of the list.
void moveFront(List L) {
  if (length(L) == 0) {
    //printf("List Warning: attempt to move to front element on null list\n");
    return;
  }

  L->cursor = L->head; // move to front
  L->index = 0; // list indices start at 0
  return;
}

// moveBack()
// Moves the cursor to the backmost element of the list.
void moveBack(List L) {
  if (length(L) == 0) {
    //printf("List Warning: attempt to move to back element on null list\n");
    return;
  }

  // code for moving the cursor to the back of the list
  L->cursor = L->tail;
  L->index = length(L) - 1;
  return;
}

// movePrev()
// moves the cursor one step towards the front of L.
// if the cursor is already at the front, it becomes undefined
// if the cursor is undefined do nothing
// PRE: cursor is defined and not at front
void movePrev(List L) {

  // cursor is undefined
  if (L->cursor == NULL) {
    // do nothing
    L->index = -1; // except maybe make sure index = -1...
    return;
  }

  // cursor is already at front
  if (index(L) == 0) {
    L->index = -1;
    L->cursor = NULL;
    return;
  }

  // move the cursor towards the front one
  L->cursor = L->cursor->prev;
  L->index--;
  return;
}

// moveNext()
// moves the cursor one step towards the back of L.
// if the cursor is already at the back, it becomes undefined
// if the cursor is undefined do nothing
// PRE: cursor is defined and not at back
void moveNext(List L) {

   // cursor is undefined
  if (L->cursor == NULL) {
    // do nothing
    L->index = -1;
    return;
  }

  // cursor is already at back
  if (index(L) == length(L) - 1) {
    L->cursor = NULL;
    L->index = -1;
    return;
  }

  // move the cursor back one
  L->cursor = L->cursor->next;
  L->index++;
  return;
}

// delete()
// deletes the cursor element, making the cursor undefined
// PRE: length() > 0, index() >= 0
void delete(List L) {
  // check the precondition
  if (length(L) > 0 && index(L) >=0) {
    // create a node to store the deleted node
    Node N = NULL;

    // edge case: length(L) == 1
    if (length(L) == 1) {

      // save the head node
      N = L->head;

      // destroy the node
      L->head = L->tail = NULL;
      freeNode(&N);
      L->length--;

      // adjust the cursor (becomes undefined when length == 1)
      L->cursor = NULL;
      L->index = -1;
      return;
    }

    // cursor is at front
    if (index(L) == 0) {
      N = L->head; // same delete code as above
      L->head = L->head->next;
      freeNode(&N);
      L->head->prev = NULL;


      //L->head = L->tail; //= NULL;
      //freeNode(&N);
      //L->head->prev = NULL;
    } else if (index(L) == (length(L) - 1)) { // cursor is at back
      N = L->tail;
      L->tail->prev->next = NULL;
      L->tail = L->tail->prev;
      freeNode(&N);
    } else { // else cursor is somewhere in between
      N = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      freeNode(&N);
    }

    // cursor goes undefined
    L->length--;
    L->cursor = NULL;
    L->index = -1;
    return;
  }

  // when the precondition is violated
  //printf("List Error: tried delete() on NULL list or bad cursor");
  return;
}

// get()
// returns the cursor element of L
// PRE: length() > 0 and index >= 0
int get(List L) {
  // check the preconditon before returning
  if (length(L) == 0 || index(L) == -1) {
    // if precondition is violated, throw an error and exit
    printf("List Error: tried get() on NULL list or bad cursor");
  }

  return L->cursor->value;
}

// printList()
// prints the list to an outputfile named output.txt
// string representation of L as a string sequence of space-seperated integers
void printList(FILE* out, List L) {

  // save the state of the cursor.. we need to restore this..
  int previous_state = index(L);

  // move the cursor to the front of L
  moveFront(L);

  // loop through and print each element to the output file 'Output.txt' in
  // the format specified by pa.
  while(L->cursor != NULL) {
    fprintf(out, "%d " , get(L));
    moveNext(L);
  }
  fprintf(out, "\n");

  // restore the cursor state
  moveFront(L);
  for (int i = 0; i < previous_state; i++) {
    // move the cursor forward one
    moveNext(L);
  }
  // cursor state restored
}


// insertBefore()
// inserts an element before the cursor if it is defined
void insertBefore(List L, int data) {

    if (index(L) == -1) {
      //printf("List Error: tried insertBefore on bad cursor");
      return;
    }


    if (index(L) == 0) {
       L->head->prev = newNode(data);
       L->head->prev->next = L->head;
       L->head = L->head->prev;

       L->length++;
       L->index++;
    } else {
      Node N = newNode(data);
      N->next = L->cursor;
      N->prev = L->cursor->prev;
      N->prev->next = N;
      L->cursor->prev = N;

      L->length++;
      L->index++;
    }
 }

// insertAfter()
// inserts an element after the cursor
void insertAfter(List L, int data) {

   if (index(L) == -1) {
     //printf("List Error: tried insertBefore on bad cursor");
     return;
   }

   if (index(L) == (length(L) - 1)) {
     L->tail = newNode(data);
     L->cursor->next = L->tail;
     L->tail->prev = L->cursor;

     L->length++;
   } else {
     Node N = newNode(data);

     L->cursor->next->prev = N;
     L->cursor->next->prev->next = L->cursor->next;
     L->cursor->next = N;
     L->cursor->next->prev = L->cursor;

     L->length++;
   }
 }

// clear()
// clears the contents of the list
void clear(List L) {
   while(length(L) > 0) {
     deleteFront(L);
   }
   L->length = 0;
   return;
 }

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state
// of the cursor in L. The List L is unchanged.
List copyList(List L) {
  List NewList = newList();

  moveFront(L);
  while(index(L) >= 0) {
    append(NewList, get(L));
    moveNext(L);
  }

  moveFront(L);
  moveFront(NewList);

  return NewList;
}

// set()
// Overwrites the cursor element with x.
// Pre: length() > 0, index() >= 0.
void set(List L, int x) {
  // if the list is length 0 or the cursor is undefined
  if (length(L) == 0 || index(L) == -1) {
    // do nothing
    return;
  }

  // direct set of the cursor's value
  L->cursor->value = x;
  return;

}

// equals(List A, List B)
// returns 0 or 1 based on the equality/state of two given lists (A and B)
int equals(List A, List B) {
  // set cursors to the front
  moveFront(A);
  moveFront(B);

  // loop to move through cursors until one or both become undefined
  while(A->cursor != NULL && B->cursor != NULL) {

    // direct element comparison
    if (get(A) != get(B))
      return 0;

    // move the cursors
    moveNext(A);
    moveNext(B);
  }

  // if only one became undefined, return false
  if (A->cursor != NULL || B->cursor != NULL) {
    return 0;
  }

  // return true because both cursors went undefined at the same time
  return 1;
}
