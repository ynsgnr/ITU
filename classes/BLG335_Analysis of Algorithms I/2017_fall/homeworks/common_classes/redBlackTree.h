#ifndef RBT_H
#define RBT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
*/

//DATA can be any type of class that supports << (stream out) and  = (assignment)
//there is no action on DATA other than print
//KEY class must implement < (smaller than), << (stream out) and = (assignment) operators

template <class KEY, class DATA>
class redBlackTree{
public:
  redBlackTree();
  ~redBlackTree();
  void print();
  void insert(KEY,DATA);

private:
  redBlackTree<KEY,DATA>  * left;
  redBlackTree<KEY,DATA>  * right;
  redBlackTree<KEY,DATA>  * parent;
  int color;
  KEY key;
  DATA data;
  void printNode(redBlackTree<KEY,DATA> *,int);
  void leftRotate(redBlackTree<KEY,DATA> *);
  void rightRotate(redBlackTree<KEY,DATA> *);
};

#include "redBlackTree.cpp"

#endif // RBT_H
