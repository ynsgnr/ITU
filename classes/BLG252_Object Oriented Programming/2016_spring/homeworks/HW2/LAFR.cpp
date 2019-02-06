#include "LAFR.h"
#include "ARTL.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

void LAFR::add(int tmpD){
	node* tmp=tail;
	tail=new node(tmp,tmpD);
	if(nodeCount==0){
		head=tail;
	}
	nodeCount++;
}
void LAFR::remove(){
	node* tmp=head;
    head=tmp->getNext();
	delete tmp;
	nodeCount--;
	if(nodeCount==0){
        tail=nullptr;
	}
}
void LAFR::setTraverser(){
	traverser = new ARTL;
    traverser->current=tail;
}

LAFR::LAFR(){
	nodeCount=0;
    tail=nullptr;
    head=nullptr;
	this->setName("LAFR");
}

LAFR::~LAFR(){
	delete traverser;
	this->removeAll();
}
