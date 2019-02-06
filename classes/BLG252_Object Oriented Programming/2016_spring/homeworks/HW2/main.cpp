#include <cstring>
#include <iostream>

#include "FALR.h"
#include "FAFR.h"
#include "LAFR.h"
#include "LALR.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
* Tested System:ITU SSH
* Compiled with command:
* g++ -std=c++11 AdderRemover.cpp ARTF.cpp ARTL.cpp ARTraverser.cpp FAFR.cpp FALR.cpp LAFR.cpp LALR.cpp main.cpp node.cpp -o hw2
* */


int main(int argc, char **argv) {

  AdderRemover *myList[4];

  myList[0] = new FAFR();
  myList[1] = new LALR();
  myList[2] = new FALR();
  myList[3] = new LAFR();

  for(int j=0; j<4; j++) {
    for(int i=0; i<5; i++)
      myList[j]->add(i);
  }

  for(int j=0; j<4; j++){
    myList[j]->remove();
    myList[j]->display();
    myList[j]->removeAll();
    myList[j]->display();
  }

    std::cout << std::endl << "Test case for ARTraverser"<< std::endl;
  for(int j=0; j<4; j++) {
    for(int i=0; i<5; i++)
      myList[j]->add(i);
    myList[j]->remove();
  }

  for(int j=0; j<4; j++){
    myList[j]->setTraverser();
    myList[j]->traverse();
  }

  return 0;
}
