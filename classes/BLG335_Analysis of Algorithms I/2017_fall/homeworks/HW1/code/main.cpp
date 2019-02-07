#ifdef DEBUG
#define DEBUGMODE(code) code
#else
#define DEBUGMODE(code)
#endif

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
#include "fileProcess.h"
#include "cardManager.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* compiled with command:
* g++ -std=c++11 main.cpp
*/

int main(int argc, char *argv[]) {
  fileProcess fp;
  cardManager cm;

  std::string input;
  std::string output;
  std::string sortType;
  std::string sortAlgo;

  clock_t startTime;
  clock_t endTime;

  if(argc==5){
    input=argv[3];
    output=argv[4];
  }else if(argc==4){
    input=argv[3];
    output=argv[3];
    output=output.substr(0,output.find(".txt"))+"-sorted.txt";
  }else{
    std::cout << "Wrong input" << '\n';
    return -1;
  }

  sortType=argv[1];
  sortAlgo=argv[2];

  try{
    fp.openFile(input);
    cm.setData(fp.getData());
  }catch(const char* msg){
    std::cout<<msg<<std::endl;
  }

  if(sortType.find("full")==1){
    startTime=clock();
    try{
      cm.fullSort(*(sortAlgo.substr(1,1).c_str()));
    }catch(const char* msg){
      std::cout<<msg<<std::endl;
    }
    endTime=clock();
  }else if(sortType.find("filter")==1){
    startTime=clock();
    try{
      cm.filterSort(*(sortAlgo.substr(1,1).c_str()));
    }catch(const char* msg){
      std::cout<<msg<<std::endl;
    }
    endTime=clock();
  }else{
    std::cout << "Wrong input" << '\n';
    return -1;
  }

  try{
    fp.openFile(output);
    fp.setNewContent(cm.getData());
    fp.writeContentToFile(1);
  }catch(const char* msg){
    std::cout<<msg<<std::endl;
  }

  std::cout << "Time elapsed: " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';

  return 0;
}
