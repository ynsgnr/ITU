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
#include <vector>
#include "fileProcess.h"
#include "redBlackTree.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* compiled with command:
* g++ -std=c++11 main.cpp
* you can use -DDEBUG for debug mode that prints pretty much everything
* and you can also use -DNONAUGMENTED for using as a regular RB tree
*/

class satelliteData {
  public:
    int age;
    char gender;
};

std::ostream& operator <<(std::ostream& out, const satelliteData& data){
  out << data.age << "-" << data.gender;
}

int main(int argc, char *argv[]) {
  fileProcess fp;
  std::string input;
  satelliteData data;
  clock_t startTime;
  clock_t endTime;

  //redBlackTree<std::string,std::string> * tree = new redBlackTree<std::string,std::string>;
  //redBlackTree<std::string,satelliteData> * tree = new redBlackTree<std::string,satelliteData>;
  redBlackTree<std::string,int> * tree = new redBlackTree<std::string,int>;

  if(argc==2){
    input=argv[1];
  }else if(argc==1){
    input=std::string("input.txt");
  }
  else{
    std::cout << "Wrong input" << '\n';
    return -1;
  }

  try{
    fp.openFile(input);
    fp.parseFile();
  }catch(const char* msg){
    std::cout<<"Input file can not opened"<<std::endl;
    std::cout<<msg<<std::endl;
    return -1;
  }

  DEBUGMODE(std::cout << "File opened creating tree" << '\n';)

  int row = fp.getRowCount();
  for(int i=0;i<row;i++){
    /*satelliteData=fp[i][2];
    satelliteData+="-";
    satelliteData+=fp[i][1];
    DEBUGMODE(std::cout << "Data: " << satelliteData << '\n';)*/
    /*data.age=std::stoi(fp[i][2]);
    data.gender=*(fp[i][1].c_str());*/
    //key,gender,data(in this case age) gender used to implement num_man and num_woman
    //so gender can not be in satelliteData anymore
    tree->insert(fp[i][0],*(fp[i][1].c_str()),std::stoi(fp[i][2]));
  }
  std::cout << '\n';
  tree->print();


  std::cout << '\n';
  std::cout<< "3rd woman: "<< tree->findWomanOnOrder(3) << '\n';
  std::cout << "4th man: "<< tree->findManOnOrder(4) << '\n';

  /*for(int i=1;i<=10;i++)
    std::cout<< i <<"th woman: "<< tree->findWomanOnOrder(i) << '\n';

  for(int i=1;i<=10;i++)
      std::cout << i << "th man: "<< tree->findManOnOrder(i) << '\n';*/


  delete tree;
}
