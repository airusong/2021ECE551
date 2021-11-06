#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
class myexception : std::exception {
 public:
  virtual const char * what() const throw() { return "index is wrong\n"; }
};
template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(const T & item, Node * n1, Node * n2) : data(item), next(n1), prev(n2) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp(rhs);
      std::swap(temp.head, head);
      std::swap(temp.tail, tail);
      std::swap(temp.size, size);
    }
    return *this;
  }

  bool remove(const T & item) {
    Node * traverse = head;
    while (traverse != NULL && traverse->data != item) {
      traverse = traverse->next;
    }
    if (traverse == NULL) {
      return false;
    }
    Node * nextN = traverse->next;
    Node * prevN = traverse->prev;
    if (nextN != NULL) {
      nextN->prev = prevN;
    }
    else {
      tail = prevN;
    }
    if (prevN != NULL) {
      prevN->next = nextN;
    }
    else {
      head = nextN;
    }
    size -= 1;
    delete traverse;
    return true;
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }
  int getSize() const { return size; }
  int find(const T & item) const {
    Node * curr = head;
    int pos = 0;
    while (curr != NULL) {
      if (item == curr->data) {
        break;
      }
      pos++;
      curr = curr->next;
    }
    if (curr == NULL) {
      return -1;
    }
    return pos;
  }
  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw myexception();
    }
    Node * curr = head;
    int pos = 0;
    while (curr != NULL) {
      if (pos == index) {
        break;
      }
      curr = curr->next;
      pos++;
    }
    return curr->data;
  }
  T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw myexception();
    }
    Node * curr = head;
    int pos = 0;
    while (curr != NULL) {
      if (pos == index) {
        break;
      }
      curr = curr->next;
      pos++;
    }
    return curr->data;
  }
  friend void testList(void);
};

//YOUR CODE GOES HERE

#endif
