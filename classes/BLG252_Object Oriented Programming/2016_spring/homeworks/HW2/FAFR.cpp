#include "FAFR.h"
#include "ARTF.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

void FAFR::add(int tmpD){
	node* tmp=head;
	head=new node(tmpD,tmp);
	if(nodeCount==0){
		tail=head;
	}
	nodeCount++;
}
void FAFR::remove(){
	node* tmp=head;
    head=tmp->getNext();
	delete tmp;
	nodeCount--;
	if(nodeCount==0){
        tail=nullptr;
	}
}

void FAFR::setTraverser(){
    traverser = new ARTF;
    traverser->current=head;
}

FAFR::FAFR(){
	nodeCount=0;
    head=nullptr;
    tail=nullptr;
	this->setName("FAFR");
}

FAFR::~FAFR(){
	delete traverser;
	this->removeAll();
}
