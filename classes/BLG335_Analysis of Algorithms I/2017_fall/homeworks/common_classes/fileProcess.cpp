#ifdef DEBUG
#define DEBUGMODE(code) code
#else
#define DEBUGMODE(code)
#endif

#ifndef FILEP_CPP
#define FILEP_CPP

#include "fileProcess.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

fileProcess::fileProcess(){
  row=0;
  column=0;
  contentAvaliable=false;
}

fileProcess::fileProcess(std::string fileToOpen){
  openFile(fileToOpen);
  row=0;
  column=0;
  contentAvaliable=false;
}

fileProcess::~fileProcess(){
  file.close();
}

/*open file for reading and writing*/
void fileProcess::openFile(std::string fileToOpen){
  DEBUGMODE(std::cout<<"openning file"<<std::endl;)
  location=fileToOpen;
  //Open file specificed in input
  if(file.is_open()){
    file.close();
  }
  file.open(fileToOpen.c_str(), std::fstream::in | std::fstream::out);
  if (!file.is_open()){
    DEBUGMODE(std::cout << "File does not exist or can not open" << '\n';)
    file.open(fileToOpen.c_str(), std::fstream::in | std::fstream::out| std::fstream::trunc);
    if (!file.is_open()) throw "can not open file";
  }
}

/* parse file into to string table*/
void fileProcess::parseFile(int i){

  DEBUGMODE(std::cout<<"parsing file"<<std::endl;)

  std::string line;
  std::string tmp;
  row=0;
  column=0;

  DEBUGMODE(std::cout << "Calculating size: "<<row<<"-"<<column << '\n';)
  if(file.is_open()){
    if(i==0){
    getline(file,line);
    if(std::count(line.begin(), line.end(), '\n')>0)row++;
    //get first line to determine column number
    column=std::count(line.begin(), line.end(), '\t');
    column++; //started from 0 and only between columns tab exists
    while (!file.eof()){
      getline(file,line);
      //if(std::count(line.begin(), line.end(), '\t')>0)row++;
      if(std::count(line.begin(), line.end(), '\t')>0)row++;
    }
    //Add one bc it started from 0
    row++;
  }else{
    getline(file,line);
    //get first line to determine column number
    column=std::count(line.begin(), line.end(), '\t');
    column++; //started from 0 and only between columns tab exists
    row=i;
  }
    DEBUGMODE(std::cout << "Size calculated: "<<row<<"-"<<column << '\n';)

    //Reset stream
    file.clear();
    file.seekg(0, std::ios::beg);

    //Allocate space for table
    DEBUGMODE(std::cout<<"processing file"<<std::endl;)
    contents.resize(row);
    for (int r=0;r<row;r++){
      contents[r].resize(column);
    }

    DEBUGMODE(std::cout << "memory allocated" << '\n';)

    for(int r=0;r<row;r++){
      getline(file,line);
      //Next row
      for(int c=0;c<column;c++){
        //Next column
        contents[r][c]=line.substr(0, line.find("\t"));
        line=line.substr(line.find("\t")+1,line.size());
      }
    }
    contentAvaliable=true;
  }
  else throw "File not open";
}

int fileProcess::getColumnCount() const{
  if (!contentAvaliable){
    throw "Content not created!";
    return -1;
  }
  return column;
}

int fileProcess::getRowCount() const{
  if (!contentAvaliable){
    throw "Content not created!";
    return -1;
  }
  return row;
}

void fileProcess::setNewContent(std::string* contentToSet,int rw,int cl){
  contents.clear();
  row=rw;
  column=cl;
  //Allocate space for table and write data
  contents.resize(row);
  for (int r=0;r<row;r++){
    contents[r].resize(column);
    for (int c=0;c<column;c++){
      contents[r][c]=contentToSet[r][c];
    }
  }
  contentAvaliable=true;
}

void fileProcess::setNewContent(std::vector< std::vector<std::string> > contentToSet){
  contents.clear();
  row=contentToSet.size();
  column=contentToSet[0].size();
  //Allocate space for table and write data
  contents.resize(row);
  for (int r=0;r<row;r++){
    contents[r].resize(column);
    for (int c=0;c<column;c++){
      contents[r][c]=contentToSet[r][c];
    }
  }
  contentAvaliable=true;
}

void fileProcess::writeContentToFile(int i){
  if(i>0){
    //dismiss content
    file.close();
    file.open(location,std::fstream::in | std::fstream::out| std::fstream::trunc);
  }
  writeContentToFile();
}

void fileProcess::writeContentToFile(){
  DEBUGMODE(std::cout << "Writing to the file" << '\n' << "Size: "<<row<<"-"<<column<<"\n";)
  if(file.is_open()){
    for (int r=0;r<row;r++){
      for(int c=0;c<(column-1);c++){
        file<<contents[r][c]<<"\t";
      }
      //For last element use endl instead of tab
      file<<contents[r][column-1]<<std::endl;
    }
    DEBUGMODE(std::cout << "writing completed" <<"\n";)
  }else{
    throw "File is not opened";
  }
}

const std::vector<std::string> fileProcess::operator[](int i) const{
  if (!contentAvaliable){
    throw "Content not created!";
  }
  return contents[i];
}

const std::vector< std::vector<std::string> > fileProcess::getData() const{
  return contents;
}

std::vector< std::vector<std::string> >::iterator fileProcess::getIterator(){
  return contents.begin();
}

void fileProcess::addColumn(int i){
  column++;
  for(int r=0;r<row;r++){
    contents[r].resize(column);
  }
}

#endif
