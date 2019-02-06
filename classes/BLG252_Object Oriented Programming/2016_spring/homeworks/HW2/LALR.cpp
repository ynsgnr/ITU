#include "LALR.h"
#include "ARTL.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

void LALR::add(int tmpD){
	node* tmp=tail;
	tail=new node(tmp,tmpD);
	if(nodeCount==0){
		head=tail;
	}
	nodeCount++;
}
void LALR::remove(){
	node* tmp=tail;
    tail=tmp->getPrev();
	delete tmp;
	nodeCount--;
	if(nodeCount==0){
        head=nullptr;
	}
}
void LALR::setTraverser(){
	traverser = new ARTL;
    traverser->current=tail;
}

LALR::LALR(){
	nodeCount=0;
    tail=nullptr;
    head=nullptr;
	this->setName("LALR");
}

LALR::~LALR(){
	delete traverser;
	this->removeAll();
}
