#ifndef BOOKCHAR_H
#define BOOKCHAR_H

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
*/
#include <string>

class bookChar{
public:
    bookChar(int p,int l=0,int i=0, char c=' ');
    bookChar(std::string p="0",std::string l="0",std::string i="0",std::string c=" ");
    int page;
    int line;
    int index;
    char character;
    int key;
};

#include "bookChar.cpp"

#endif // BOOKCHAR_H
