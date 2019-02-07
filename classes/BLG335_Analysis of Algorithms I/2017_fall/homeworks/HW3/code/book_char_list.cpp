#ifndef LIST_CPP
#define LIST_CPP

#include "book_char_list.h"
#include "bookChar.h"
#include <list>

void book_char_list::insert(bookChar c){
  bookCharList.push_back(c);
}

bookChar book_char_list::lookup(int key){
  std::list<bookChar>::iterator it;
  it = bookCharList.begin();
  while(it!=bookCharList.end() && (*it).key!=key)
    ++it;
  if((*it).key==key)
    return *it;
  return bookChar();
}

#endif
