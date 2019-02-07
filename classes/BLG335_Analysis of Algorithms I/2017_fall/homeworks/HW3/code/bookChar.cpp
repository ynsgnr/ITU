#ifndef BOOKCHAR_CPP
#define BOOKCHAR_CPP

#include "bookChar.h"
#include <stdlib.h>
#include <string>

bookChar::bookChar(int p, int l,int i,char c){
  page=p;
  line=l;
  index=i;
  character=c;
  key=i+100*l+10000*p;
}

bookChar::bookChar(std::string p, std::string l,std::string i,std::string c){
  page=atoi(p.c_str());
  line=atoi(l.c_str());
  index=atoi(i.c_str());
  character=*(c.c_str());
  key=index+100*line+10000*page;
}

#endif
