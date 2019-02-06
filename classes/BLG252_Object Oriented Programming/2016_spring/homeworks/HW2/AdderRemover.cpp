#include "AdderRemover.h"
#include <iostream>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

void AdderRemover::display() const{
	node* tmp=head;
	std::cout<<name<<" | NodeCount:"<<nodeCount<<std::endl<<"------"<<std::endl;
	if(nodeCount==0){
		std::cout<<"There is no element to print"<<std::endl;
	}
	else
	for(int i=0;i<nodeCount;i++){
        std::cout<<tmp->getData()<<std::endl;
        tmp=tmp->getNext();
	}
    std::cout<<std::endl;
}

void AdderRemover::removeAll(){
    for(int i=0;i<nodeCount;i++){
        delete head;
        head=head->getNext();
    }
    nodeCount=0;
}

void AdderRemover::traverse() const{
    std::cout<<name<<" | NodeCount:"<<nodeCount<<std::endl<<"------"<<std::endl;
    for(int i=0;i<nodeCount;i++){
    std::cout<<traverser->next()<<std::endl;
    }
    std::cout<<std::endl;
}

void AdderRemover::setName(std::string tmp){
	name=tmp;
}

std::string AdderRemover::getName() const{
	return name;
}
