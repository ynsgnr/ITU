#include "SmallVector.h"
#include <cstring>
#include <iostream>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 27.03.2017
*/

void SmallVector::expand(int neededSpace){
    int allocatedSpace=vectorSize-STATIC_SIZE;
    if(allocatedSpace>0){
        //dynamicBuffer exists
        int *p=new int[allocatedSpace+neededSpace] ;
        for(int i=0;i<allocatedSpace;i++){
            p[i]=dynamicBuffer[i];
        }
        delete[] dynamicBuffer;
        dynamicBuffer=p;
    }
    else{
        //dynamicBuffer doesnt exist
        dynamicBuffer=new int[neededSpace];
    }
}

void SmallVector::shrink(int notNeeded){
    int allocatedSpace=vectorSize-STATIC_SIZE;
    int newSpace=allocatedSpace-notNeeded+1;
    if(allocatedSpace>0){
        if(newSpace<0){
            //new size fits in staticBuffer, delete dynamicBuffer
            delete [] dynamicBuffer;
        }
        else{
            //need less space for dynamicBuffer
            int *p=new int[newSpace] ;
            for(int i=0;i<newSpace;i++){
                p[i]=dynamicBuffer[i];
            }
            delete[] dynamicBuffer;
            dynamicBuffer=p;
        }
    }
    //else no need to shrink alredy, vector is in staticbuffer
}

SmallVector::SmallVector()
{
    //Empty Constructor
    vectorSize=0;
}

SmallVector::SmallVector(int* data, int dataSize)
{
    //Constructor with data
    if(dataSize>=STATIC_SIZE){
        //Allocate new space
        dynamicBuffer = new int[dataSize-STATIC_SIZE];
        int i;
        for(i=0;i<STATIC_SIZE;i++){
            staticBuffer[i]=data[i];
        }
        for(;i<=dataSize;i++){
            dynamicBuffer[i-STATIC_SIZE]=data[i];
        }
    }
    else{
        //Fits in staticBuffer
        for(int i=0;i<=dataSize;i++){
            staticBuffer[i]=data[i];
        }
    }
    vectorSize=dataSize-1;
}


SmallVector::SmallVector(const SmallVector &vector2copy)
{
    //Copy Constructor
    vectorSize=vector2copy.getSize()-1;
    int allocatedSpace = vectorSize-STATIC_SIZE+1;
    if(allocatedSpace<0){
        //Fits in static buffer
        for (int i=0;i<vectorSize;i++){
            staticBuffer[i]=vector2copy[i];
        }
    }
    else{
        //Does not fit in static buffer
        //Allocate new space
        dynamicBuffer = new int[vectorSize-STATIC_SIZE];
        int i;
        for(i=0;i<STATIC_SIZE;i++){
            staticBuffer[i]=vector2copy[i];
        }
        for(;i<=vectorSize;i++){
            dynamicBuffer[i-STATIC_SIZE]=vector2copy[i];
        }
    }
}

int SmallVector::getSize() const {
    return vectorSize+1;
}

int SmallVector::pop_back(){
    int result;
    if (vectorSize>=STATIC_SIZE){
        //Pop from dynamicBuffer
        result = dynamicBuffer[vectorSize-STATIC_SIZE];
        shrink(1);
    }
    else{
        //Pop from staticBuffer
        result=staticBuffer[vectorSize];
    }
    vectorSize--;
    return result;
}

void SmallVector::push_back(int data=0){
    vectorSize++;
    if(vectorSize-STATIC_SIZE<0){
        staticBuffer[vectorSize]=data;
    }
    else{
        expand(1);
        dynamicBuffer[vectorSize-STATIC_SIZE]=data;
    }
}

void SmallVector::push_back(int* data,int dataSize){
    int allocatedSpace = vectorSize-STATIC_SIZE;
    if(allocatedSpace<0){
        //No dynamic array
        int i=vectorSize+1;
        int j=0;
        while(i<STATIC_SIZE && j<dataSize){
            staticBuffer[i++]=data[j++];
        }
        if(j<dataSize){
            //Need new space
            expand(dataSize-j);
            i=0;
            while(j<dataSize){
                dynamicBuffer[i++]=data[j++];
            }
        }
    }
    else{
        //Need new space
        expand(dataSize);
        for(int i=0;i<dataSize;i++){
            dynamicBuffer[allocatedSpace+i+1]=data[i];
        }
    }
    vectorSize+=dataSize;
}

SmallVector SmallVector::reverse() const{
    int i = vectorSize;
    int result[vectorSize];
    int j=0;
    //Create an array in reverse order
    while(i>=0){
        if (i>=STATIC_SIZE){
            result[j++]=dynamicBuffer[i-STATIC_SIZE];
        }
        else{
            result[j++]=staticBuffer[i];
        }
        i--;
    }
    return SmallVector(result,vectorSize+1);
}

//[] for non const vectors, can modified
int& SmallVector::operator[](int i){
    //Normalize i:
    if(i<0){
        //Negative numbers
        i+=vectorSize+1;
        if(i<0){
            return staticBuffer[0];
        }
    }
    else if(i>vectorSize){
        //Numbers bigger than vectorSize
        i=vectorSize;
    }

    //Get data at i:
    if (i>=STATIC_SIZE){
        return dynamicBuffer[i-STATIC_SIZE];
    }
    else{
        return staticBuffer[i];
    }
}

//[] for const vectors, cant modified
int SmallVector::operator[](int i) const{
    //Normalize i:
    if(i<0){
        //Negative numbers
        i+=vectorSize+1;
        if(i<0){
            return staticBuffer[0];
        }
    }
    else if(i>vectorSize){
        //Numbers bigger than vectorSize
        i=vectorSize;
    }

    //Get data at i:
    if (i>=STATIC_SIZE){
        return dynamicBuffer[i-STATIC_SIZE];
    }
    else{
        return staticBuffer[i];
    }
}

const SmallVector& SmallVector::operator=(const SmallVector& object){
    if(vectorSize>=STATIC_SIZE){
        //Clean object
        delete[] dynamicBuffer;
    }
    vectorSize=object.getSize()-1;
    if(vectorSize>=STATIC_SIZE){
        //Allocate new space
        dynamicBuffer = new int[vectorSize-STATIC_SIZE+1];
        int i;
        for(i=0;i<STATIC_SIZE;i++){
            staticBuffer[i]=object[i];
        }
        for(;i<=vectorSize;i++){
            dynamicBuffer[i-STATIC_SIZE]=object[i];
        }
    }
    else{
        //Fits in staticBuffer
        for(int i=0;i<=vectorSize;i++){
            staticBuffer[i]=object[i];
        }
    }
    return *this;
}

SmallVector SmallVector::operator+(const SmallVector& rightSide) const{
    int rSize = rightSide.getSize()+vectorSize+1;
    int result [rSize];
    int i;
    for (i=0;i<=vectorSize;i++){
        result[i]=this->operator[](i);
    }
    //i equals vectorSize. Must be decresed to access rightSide's all elements
    i--;
    for(;i<rSize;i++){
        result[i+1]=rightSide[i-vectorSize];
    }
    return SmallVector(result,rSize);
}

SmallVector SmallVector::operator*(const int& rightSide) const{
    int rSize = (vectorSize+1)*rightSide;
    int result [rSize];
    int arrayCounter=0,vectorCounter;
    for(int i=0;i<rightSide;i++){
        vectorCounter=0;
        while(vectorCounter<=vectorSize){
            result[arrayCounter++]=this->operator[](vectorCounter++);
        }
    }
    return SmallVector(result,rSize);
}


SmallVector::~SmallVector()
{
    if(vectorSize>=STATIC_SIZE)
    delete[] dynamicBuffer;
}