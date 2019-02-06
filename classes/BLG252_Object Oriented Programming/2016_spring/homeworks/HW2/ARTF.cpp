#include "ARTF.h"
#include <iostream>
bool ARTF::hasNode() const{
    return current!=nullptr;
}

int ARTF::next(){
    if(ARTF::hasNode()){
        int tmp=current->getData();
        current=current->getNext();
		return tmp;
	}else{
        std::cout<<"Dont have a node!"<<std::endl;
        return -1;
	}
}

ARTF::~ARTF()
    {}
