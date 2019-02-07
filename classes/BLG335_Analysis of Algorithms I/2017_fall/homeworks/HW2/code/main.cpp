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

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* compiled with command:
* g++ -std=c++11 main.cpp
*/

int partition(std::vector< std::vector<std::string> >::iterator it,int p,int r){
  int population,i;
  std::string geoId;
  std::vector< std::vector<std::string> >::iterator tmp;
  int currentNum;
  tmp=std::next(it, r);
  population=stoi((*tmp)[0]);
  geoId=(*tmp)[5];
  DEBUGMODE(
    std::cout << "contents in partion" << '\n';
    std::cout << "population:" << population <<std::endl;
    std::cout << "geoID:" << geoId <<std::endl;
    std::cout << "i:" << i <<std::endl;
    std::cout << "p:" << p <<std::endl;
    std::cout << "r:" << r <<std::endl;
  )
  i=p-1;
  for(int j=p;j<r;j++){
    currentNum=stoi((*std::next(it, j))[0]);
    if(currentNum<population || (currentNum==population && (*std::next(it, j))[5]<=geoId)){
      i++;
      //exchange A[i] A[j]
      (*std::next(it, i)).swap(*std::next(it, j));
    }
  }
  //exchange A[i+1] A[r]
  i++;
  (*std::next(it, i)).swap(*std::next(it, r));
  return i;
}


void quicksort(std::vector< std::vector<std::string> >::iterator it,int p,int r){
  int q;
  if(p<r){
    q=partition(it,p,r);
    quicksort(it,p,q-1);
    quicksort(it,q+1,r);
  }
}

int main(int argc, char *argv[]) {
  fileProcess fp;

  std::string input;

  int n;

  std::vector< std::vector<std::string> >::iterator it;

  clock_t startTime;
  clock_t endTime;

  if(argc==3){
    input=argv[1];
    n=atoi(argv[2]);
  }else if(argc==2){
    input=argv[1];
    n=0;
  }else{
    std::cout << "Wrong input" << '\n';
    return -1;
  }

  try{
    fp.openFile(input);
    fp.parseFile(n+1);
  }catch(const char* msg){
    std::cout<<msg<<std::endl;
  }
  it=fp.getIterator();

  startTime=clock();

  //apply quicksort
  quicksort(it,1,n); //starts from 0 and first row is useless

  endTime=clock();

  std::cout << "Time elapsed: " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';

  try{
    //writeContentToFile
    fp.openFile(input.substr(0,input.find(".csv"))+"-sorted.csv");
    fp.writeContentToFile(1);
  }catch(const char* msg){
    std::cout<<msg<<std::endl;
  }
  return 0;
}
