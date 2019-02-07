#ifndef FILEP_H
#define FILEP_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* This class reads csv file's
* contents in form of a string array
* This class created using fileProcess
* class from assignment 1 and assignment 2 of Yunus Güngör
*/

class fileProcess{
public:
    fileProcess(std::string);
    fileProcess();
    ~fileProcess();
    void openFile(std::string);
    const std::vector<std::string> operator[](int) const;
    int getColumnCount() const;
    int getRowCount() const;
    void setNewContent(std::string*,int,int);
    void setNewContent(std::vector< std::vector<std::string> >);
    void writeContentToFile();
    void writeContentToFile(int);
    std::vector< std::vector<std::string> >::iterator getIterator();
    const std::vector< std::vector<std::string> > getData() const;
    void parseFile(int i=0);
    void addColumn(int i=1);
private:
    std::string location;
    int column=0;
    int row=0;
    bool contentAvaliable;
    std::vector< std::vector<std::string> > contents;
    std::fstream file;
};

#include "fileProcess.cpp"

#endif // FILEP_H
