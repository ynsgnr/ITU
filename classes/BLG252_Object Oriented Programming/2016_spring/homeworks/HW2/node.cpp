#include "node.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 27.03.2017
*/

node::node(){
	data=0;
    next=nullptr;
    prev=nullptr;
}

node::node(node* tmp,int tmpD){
    //Add new node to right of the node (after the node)
	data=tmpD;
    if(tmp==nullptr){
        prev=nullptr;
        next=nullptr;
    }
    else{
        next=tmp->getNext();
        tmp->setNext(this);
        prev=tmp;
    }
}

node::node(int tmpD,node* tmp){
    //Add new node to left of the node (before the node)
	data=tmpD;
    if(tmp==nullptr){
        prev=nullptr;
        next=nullptr;
    }
    else{
        prev=tmp->getPrev();
        tmp->setPrev(this);
        next=tmp;
    }
}

void node::setData(int tmp) {
	data=tmp;
}
void node::setNext(node* tmp){
	next=tmp;
}
void node::setPrev(node* tmp){
	prev=tmp;
}

int node::getData() const{
	return data;
}

node* node::getNext() const{
	return next;
}

node* node::getPrev() const{
	return prev;
}
