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
#include "dictionary.h"
#include "book_char_list.h"
#include "bookChar.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* compiled with command:
* g++ -std=c++11 main.cpp
*/

int main(int argc, char *argv[]) {
  fileProcess fp;
  std::string input;
  std::string input2;
  int n;
  int averageCollisions[4];
  int tmpCollision;
  book_char_list bookCharList;
  dictionary d;

  std::vector< std::vector<std::string> >::iterator row;
  std::vector<std::string>::iterator column;

  clock_t startTime;
  clock_t endTime;

  if(argc==3){
    input=argv[1];
    input2=argv[2];
  }else if(argc==2){
    input=argv[1];
    input2=std::string("ds-set-lookup.txt");
  }else if(argc==1){
    input=std::string("ds-set-input.txt");
    input2=std::string("ds-set-lookup.txt");
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

  std::cout << "DICTIONARY" << '\n';

  averageCollisions[0]=0;
  averageCollisions[1]=0;
  averageCollisions[2]=0;
  averageCollisions[3]=0;

  int r=0;

  row=fp.getIterator();
  startTime=clock();
  if(fp.getRowCount()>1000)
    for(;r<1000;r++){
      //DEBUGMODE(std::cout << "Inserting"<< (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2]<<"-"<<(*row)[3] << '\n';)
      tmpCollision = d.insert(bookChar((*row)[0],(*row)[1],(*row)[2],(*row)[3]));
      averageCollisions[0]+=tmpCollision;
      averageCollisions[1]+=tmpCollision;
      averageCollisions[2]+=tmpCollision;
      averageCollisions[3]+=tmpCollision;
      row++;
    }
  DEBUGMODE(std::cout << "First 1000 completed" << '\n';)
  if(fp.getRowCount()>10000)
    for(;r<10000;r++){
      //DEBUGMODE(std::cout << "Inserting"<< (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2]<<"-"<<(*row)[3] << '\n';)
      tmpCollision = d.insert(bookChar((*row)[0],(*row)[1],(*row)[2],(*row)[3]));
      averageCollisions[1]+=tmpCollision;
      averageCollisions[2]+=tmpCollision;
      averageCollisions[3]+=tmpCollision;
      row++;
    }
  DEBUGMODE(std::cout << "First 10000 completed" << '\n';)
  if(fp.getRowCount()>100000)
    for(;r<100000;r++){
      DEBUGMODE(std::cout << "Inserting"<< (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2]<<"-"<<(*row)[3] << '\n';)
      tmpCollision = d.insert(bookChar((*row)[0],(*row)[1],(*row)[2],(*row)[3]));
      averageCollisions[2]+=tmpCollision;
      averageCollisions[3]+=tmpCollision;
      row++;
    }
  DEBUGMODE(std::cout << "First 100000 completed" << '\n';)
  for(;r<fp.getRowCount();r++){
    DEBUGMODE(std::cout << "Inserting "<<r<<" "<< (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2]<<"-"<<(*row)[3] << '\n';)
    tmpCollision = d.insert(bookChar((*row)[0],(*row)[1],(*row)[2],(*row)[3]));
    averageCollisions[3]+=tmpCollision;
    row++;
  }
  endTime=clock();
  DEBUGMODE(std::cout << "Insertion completed!" << '\n';)
  std::cout << "Insertion finished after " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';

  std::cout << "Average number of collisions (first 1.000)\t|"<< (float)averageCollisions[0]/1000 << '\n';
  std::cout << "Average number of collisions (first 10.000)\t|"<< (float)averageCollisions[1]/10000 << '\n';
  std::cout << "Average number of collisions (first 100.000)\t|"<< (float)averageCollisions[2]/100000 << '\n';
  std::cout << "Average number of collisions (overall)\t|"<< (float)averageCollisions[3]/fp.getRowCount() << '\n';

  //Look up
  try{
    fp.openFile(input2);
    fp.parseFile();
  }catch(const char* msg){
    std::cout<<"Lookup file can not opened"<<std::endl;
    std::cout<<msg<<std::endl;
    return -1;
  }

  fp.addColumn();

  row = fp.getIterator();

  char c[2];
  c[1]='\0';
  startTime=clock();
  for(r=0;r<fp.getRowCount();r++){
    DEBUGMODE(std::cout << "Looking for "<< (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2] << '\n';)
    c[0]=d.lookup(bookChar((*row)[0],(*row)[1],(*row)[2]).key).character;
    DEBUGMODE(std::cout << "Found character "<< c << "for " << (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2]<<"-"<<(*row)[3] << '\n');
    column=(*row).begin();
    column+=3;
    (*column)=std::string(c);
    row++;
  }
  endTime=clock();
  std::cout << "Lookup finished after " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';

  try{
    fp.openFile("ds-set-output-dict.txt");
  }catch(const char* msg){
    std::cout<<"Output file for dictionary can not opened"<<std::endl;
    std::cout<<msg<<std::endl;
    return -1;
  }
  fp.writeContentToFile(1);

  std::cout << "LIST" << '\n';

  try{
    fp.openFile(input);
    fp.parseFile();
  }catch(const char* msg){
    std::cout<<"Input file can not opened"<<std::endl;
    std::cout<<msg<<std::endl;
    return -1;
  }

  row = fp.getIterator();

  startTime=clock();
  for(r=0;r<fp.getRowCount();r++){
    bookCharList.insert(bookChar((*row)[0],(*row)[1],(*row)[2],(*row)[3]));
    row++;
  }
  endTime=clock();
  std::cout << "Insertion finished after " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';

  //Look up
  try{
    fp.openFile(input2);
    fp.parseFile();
  }catch(const char* msg){
    std::cout<<"Lookup file can not opened"<<std::endl;
    std::cout<<msg<<std::endl;
    return -1;
  }
  fp.addColumn();

  row = fp.getIterator();

  c[1]='\0';
  startTime=clock();
  for(r=0;r<fp.getRowCount();r++){
    DEBUGMODE(std::cout << "Looking for "<< (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2] << '\n';)
    c[0]=bookCharList.lookup(bookChar((*row)[0],(*row)[1],(*row)[2]).key).character;
    DEBUGMODE(std::cout << "Found character "<< c << "for " << (*row)[0]<<"-"<<(*row)[1]<<"-"<<(*row)[2]<<"-"<<(*row)[3] << '\n');
    column=(*row).begin();
    column+=3;
    (*column)=std::string(c);
    row++;
  }
  endTime=clock();
  std::cout << "Lookup finished after " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';

  try{
    fp.openFile("ds-set-output-list.txt");
  }catch(const char* msg){
    std::cout<<"Ouput file for list can not opened"<<std::endl;
    std::cout<<msg<<std::endl;
    return -1;
  }
  fp.writeContentToFile(1);

  return 0;
}
