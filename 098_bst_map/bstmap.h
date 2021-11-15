#ifndef _BSTMAP_H__
#define _BSTMAP_H__

#include <cstdlib>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<k, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL);
  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      Node * traverse = root;
    }
  };
#endif
