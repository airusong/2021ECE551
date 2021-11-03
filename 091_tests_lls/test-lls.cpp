#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  IntList il2;
  IntList il1;
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    il1.addFront(1);
    assert(il1.head->data == 1);
    assert(il1.head->next == NULL);
    assert(il1.head->prev == NULL);
    assert(il1.getSize() == 1);
    assert(il1.head == il1.tail);
    assert(il1[0] == 1);
    il1.addFront(2);
    assert(il1.head->next->data == 1);
    assert(il1.tail->data == 1 && il1.head->data == 2);
    assert(il1.tail->next == NULL && il1.head->prev == NULL);
    assert(il1.head->next->next == NULL && il1.tail->prev->prev == NULL);
    assert(il1.head->next == il1.tail && il1.tail->prev == il1.head);
    assert(il1.getSize() == 2);
    assert(il1[0] == 2 && il1[1] == 1);
    // WRITE ME
  }

  void testAddBack() {
    il2.addBack(1);
    il2.addBack(2);
    assert(il2.head->next->data == 2);
    assert(il2.tail->data == 2 && il2.head->data == 1);
    assert(il2.tail->next == NULL && il2.head->prev == NULL);
    assert(il2.head->next->next == NULL && il2.tail->prev->prev == NULL);
    assert(il2.head->next == il2.tail && il2.tail->prev == il2.head);
    assert(il2.getSize() == 2);
    assert(il2[0] == 1 && il2[1] == 2);
  }
  void testCopy() {
    IntList il3(il1);
    assert(il3.head->next->data == 1);
    assert(il3.tail->data == 1 && il3.head->data == 2);
    assert(il3.tail->next == NULL && il3.head->prev == NULL);
    assert(il3.head->next->next == NULL && il3.tail->prev->prev == NULL);
    assert(il3.head->next == il3.tail && il3.tail->prev == il3.head);
    assert(il3.getSize() == 2);
    assert(il3[0] == 2 && il3[1] == 1);
  }
  void testAssign() {
    IntList il4;
    il4 = il1;
    assert(il4.head->next->data == 1);
    assert(il4.tail->data == 1 && il4.head->data == 2);
    assert(il4.tail->next == NULL && il4.head->prev == NULL);
    assert(il4.head->next->next == NULL && il4.tail->prev->prev == NULL);
    assert(il4.head->next == il4.tail && il4.tail->prev == il4.head);
    assert(il4.getSize() == 2);
    assert(il4[0] == 2 && il4[1] == 1);
    il4.addBack(1);
    il2 = il4;
  }
  void testRemove() {
    assert(il1.remove(10) == false);
    assert(il1.remove(1) == true);
    assert(il1.find(1) == -1);
    assert(il1.find(2) == 0);
    assert(il1.head != NULL);
    assert(il1.head == il1.tail);
    assert(il1.head->data == 2 && il1.tail->data == 2);
    assert(il1.head->next == NULL && il1.head->prev == NULL);
    assert(il1.remove(2) == true);
    assert(il1.head == NULL && il1.tail == NULL);
    assert(il1.remove(1) == false);
    il1.addBack(3);
    il1.addBack(4);
    il1.addBack(3);
    assert(il1.remove(3) == true);
    assert(il1.head->next == il1.tail && il1.tail->prev == il1.head);
    assert(il1.head->data == 4);
    assert(il1.head->next->data == 3);
    assert(il1.head->prev == NULL);
    assert(il1.tail->next == NULL);
    assert(il1.tail->data == 3 && il1.tail->prev->data == 4);
    assert(il1.find(3) == 1);
    assert(il1.find(4) == 0);
    assert(il1.getSize() == 2);
    assert(il1.remove(4) == true);
    assert(il1.head != NULL);
    assert(il1.head == il1.tail);
    assert(il1.head->next == NULL && il1.head->prev == NULL);
    assert(il1.find(4) == -1);
    assert(il1.find(3) == 0);
    assert(il1.getSize() == 1);
    IntList il5;
    il5.addBack(1);
    il5.addBack(2);
    il5.addBack(1);
    il5.addBack(12);

    assert(il5.remove(1) == 1);
    assert(il5[0] == 2 && il5[1] == 1 && il5[2] == 12);
    assert(il5.find(1) == 1);
    assert(il5.getSize() == 3);
    assert(il5.head->data == 2 && il5.tail->data == 12 && il5.head->next->data == 1 &&
           il5.head->prev == NULL && il5.tail->prev->data == 1 && il5.tail->next == NULL);
    assert(il5.remove(1) == 1);
    assert(il5[0] == 2 && il5[1] == 12);
    assert(il5.find(1) == -1);
    assert(il5.getSize() == 2);
    IntList list1;
    list1.addBack(2);
    list1.addBack(3);
    list1.addBack(1);
    assert(list1.remove(3) == true);
    assert(list1.head->data == 2 && list1.tail->data == 1 && list1.getSize() == 2 &&
           list1.head->next->next == NULL && list1.tail->prev->prev == NULL &&
           list1.head->next->prev == list1.head && list1.tail->prev->next == list1.tail);

    //
  }

  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopy();
  t.testAssign();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
