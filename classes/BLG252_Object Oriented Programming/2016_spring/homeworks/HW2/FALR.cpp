#include "FALR.h"
#include "ARTF.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

void FALR::add(int tmpD){
	node* tmp=head;
	head=new node(tmpD,tmp);
	if(nodeCount==0){
		tail=head;
	}
	nodeCount++;
}
void FALR::remove(){
	node* tmp=tail;
    tail=tmp->getPrev();
	delete tmp;
	nodeCount--;
	if(nodeCount==0){
        head=nullptr;
	}
}
void FALR::setTraverser(){
    traverser = new ARTF;
    traverser->current=head;
}

FALR::FALR(){
	nodeCount=0;
    tail=nullptr;
    head=nullptr;
	this->setName("FALR");
}

FALR::~FALR(){
	delete traverser;
	this->removeAll();
}
