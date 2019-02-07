#ifndef FILEP_H
#define FILEP_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* This class reads a tab splitted file's
* contents in form of a string array
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
    const std::vector< std::vector<std::string> > getData() const;
private:
    std::string location;
    void parseFile();
    int column;
    int row;
    bool contentAvaliable;
    std::vector< std::vector<std::string> > contents;
    std::fstream file;
};

#include "fileProcess.cpp"

#endif // FILEP_H
