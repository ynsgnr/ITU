#ifndef LIST_H
#define LIST_H

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
*/
#include <list>
#include "bookChar.h"

class book_char_list{
public:
  void insert(bookChar);
  bookChar lookup(int);
private:
  std::list<bookChar> bookCharList;
};

#include "book_char_list.cpp"

#endif
