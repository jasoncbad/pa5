/* --------------------------------

  ListTest.c | PA4
  Programmer: Jay Montoya
  UCSC ID: jaanmont | 1742317

  Test client for List ADT for pa4.

-----------------------------------
*/
#include <stdio.h>
#include "List.h"

// main
int main(int argc, char* argv[]) {
  printf("Test client started...\n");

  // create a couple List ADT's
  List A = newList();
  List B = newList();

  //add some values
  printf("\tList A/B created..\n\tadding values...\n");
  append(A, 1337);
  append(A, 123456789);
  append(A, 987654321);
  append(A, 27272);
  append(B, 783978);
  append(B, 3);
  append(B, 89384);
  append(B, 28373);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));

  // retrieve some values
  moveFront(A); moveFront(B);
  printf("\tFront value at A is: %d\n", get(A));
  printf("\tFront value at B is: %d\n", get(B));
  moveBack(A); moveBack(B);
  printf("\tBack value at A is: %d\n", get(A));
  printf("\tBack value at B is: %d\n", get(B));

  // cursor values
  printf("\t\t\tA cursor index = %d\n", index(A));
  printf("\t\t\tB cursor index = %d\n", index(B));


  // insert before and insert after
  printf("\t\tInserting the value 420 before A's cursor... \n");
  insertBefore(A, 420);
  printf("\t\tInserting the value 420 after B's cursor... \n");
  insertAfter(B, 420);

  // cursor values
  printf("\t\t\tA cursor index = %d\n", index(A));
  printf("\t\t\tB cursor index = %d\n", index(B));

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));


  // movePrev() moveNext() tests
  movePrev(A); // move A back to the same index as B.
  printf("\tA index = %d\n", index(A));
  printf("\tB index = %d (should be the same)\n", index(B));
  moveNext(A); moveNext(B);
  moveNext(A); moveNext(B); // cursors should now be undefined
  printf("\tNow...\n\tA index = %d\n", index(A));
  printf("\tB index = %d", index(B));

  // delete the back and front elemenent
  printf("\t\tDeleting front and back elements in both lists...\n");
  deleteFront(A); deleteBack(A);
  deleteFront(B); deleteBack(B);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));

  // delete the second element in each list
  printf("\t\tDeleting the second element in each list...\n");
  moveFront(A); moveNext(A);
  moveFront(B); moveNext(B);
  delete(A); delete(B);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));

  // test our new set method
  printf("\t\tUsing our new set() method to set the first element to 0\n");
  moveFront(A); set(A, 0);
  moveFront(B); set(B, 0);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));

  // clear Lists
  printf("\t\tClearing lists...\n");
  clear(A); clear(B);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));

  // prepend elements
  printf("\t\tPrepending element 1 to A and B...\n");
  prepend(A,1); prepend(B,1);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));


  // copying C to D
  printf("\t\tCopying list B, calling it list C...\n");
  List C = copyList(B);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));
  printf("\tLIST C: "); printList(stdout, C);
  printf("\t\tlength = %d\n", length(C));

  // clear all lists
  printf("\t\tClearing all lists...\n");
  clear(A); clear(B); clear(C);

  // print the lists to console
  printf("\tLIST A: "); printList(stdout, A);
  printf("\t\tlength = %d\n", length(A));
  printf("\tLIST B: "); printList(stdout, B);
  printf("\t\tlength = %d\n", length(B));
  printf("\tLIST C: "); printList(stdout, C);
  printf("\t\tlength = %d\n", length(C));


  // clean up our mess
  freeList(&A);
  freeList(&B);
  freeList(&C);

  A = NULL;
  B = NULL;
  C = NULL;

  printf("Test client ended...\n\n");
  return 0;
}
