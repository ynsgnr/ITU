#ifndef DICTIONARY_H
#define DICTIONARY_H

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
*/

#include "bookChar.h"

#define HASHTABLESIZE 131071

class dictionary{
public:
  int insert(bookChar);
  bookChar lookup(int);
private:
  bookChar hashTable[HASHTABLESIZE];
};

#include "dictionary.cpp"

#endif
