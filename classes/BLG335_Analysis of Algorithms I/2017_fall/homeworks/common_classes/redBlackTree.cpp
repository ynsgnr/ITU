#ifdef DEBUG
#define DEBUGMODE(code) code
#else
#define DEBUGMODE(code)
#endif

#ifndef RBT_CPP
#define BRT_CPP

#include "redBlackTree.h"
#include <string>
#include <iostream>

#define PRINTTAB(x)   for(int i=0;i<x;i++){std::cout<<"\t";}
#define PRINTCOLOR(node)   node->color==1 ? std::cout << "(R)" : node->color==0 ? std::cout << "(B)" : std::cout<<"(Err)";
#define PRINTINDENTATION() node->parent->left==node ? std::cout<<char(218)<<char(196) :  std::cout<<char(192)<<char(196);

template <class KEY, class DATA>
void redBlackTree<KEY,DATA>::print(){
  printNode(this->left,1);
  //print root
  PRINTCOLOR(this)
  std::cout<<key<<"-";
  std::cout<<data<<std::endl;
  printNode(this->right,1);
}

template <class KEY, class DATA>
void redBlackTree<KEY,DATA>::printNode(redBlackTree<KEY,DATA> * node,int height){
  if(node->color!=-1){
    printNode(node->left,height+1);

    //print node
    PRINTTAB(height)
    PRINTINDENTATION()
    PRINTCOLOR(node)
    std::cout<<node->key<<"-";
    std::cout<<node->data<<std::endl;

    printNode(node->right,height+1);
  }
}

template <class KEY, class DATA>
void redBlackTree<KEY,DATA>::insert(KEY key,DATA data){
  redBlackTree<KEY,DATA> * current;
  current=this;
  DEBUGMODE(std::cout << "Adding key: " << key << '\n';)
  while(current->color!=-1){
    if(current->key<key){
      current=current->left;
    }else{
      current=current->right;
    }
  }
  //found place add new key
  DEBUGMODE(if(current->parent!=NULL) std::cout << "Adding to the node of: "<<current->parent->key <<" with color "<<current->parent->color<< '\n';)
  current->key = key;
  current->color = 1;//RED
  current->data = data;
  current->left = new redBlackTree<KEY,DATA>;
  current->left->parent = current;
  current->right= new redBlackTree<KEY,DATA>;
  current->right->parent = current;
  redBlackTree<KEY,DATA> * Parent;
  redBlackTree<KEY,DATA> * uncle;
  Parent=current->parent;
  while(Parent!=NULL and Parent->parent!=NULL and Parent->color==1){
    DEBUGMODE(std::cout << "Working on: " << Parent->key << '\n';)
    DEBUGMODE(this->print();)
    if(Parent==Parent->parent->left){
      uncle = Parent->parent->right;
      if(uncle->color==1){
        //case 1 - recolor
        DEBUGMODE(std::cout << "Recoloring: " << Parent->key <<"-"<< uncle->key <<"-"<< current->key << '\n';)
        Parent->parent->color=1;
        Parent->color=0;
        uncle->color=0;
        current=Parent->parent;
        //assign new x
        if(current!=NULL)
          Parent=current->parent;
        else
          Parent=NULL;
      }else{
        if(current==Parent->right){
          //case 2 - left rotate Parent
          DEBUGMODE(std::cout << "Left Rotate on case 2: "<< Parent->key << '\n';)
          leftRotate(Parent);
          current=current->left;
          DEBUGMODE(this->print();)
        }
        //case 3 - right rotate old grandParent new Parent
        DEBUGMODE(std::cout << "Right rotate on case 3: " << Parent->key << '\n';)
        rightRotate(Parent->parent);
        current->parent->color=0;
        if(current->parent->left->color!=-1) current->parent->left->color=1;
        if(current->parent->right->color!=-1) current->parent->right->color=1;
        //finished
        Parent=NULL;
      }
    }else{
      uncle = Parent->parent->left;
      if(uncle->color==1){
        //case 1 - recolor
        DEBUGMODE(std::cout << "Recoloring: " << Parent->key <<"-"<< uncle->key <<"-"<< current->key << '\n';)
        Parent->parent->color=1;
        Parent->color=0;
        uncle->color=0;
        current=Parent->parent;
        //assign new x
        if(current!=NULL)
          Parent=current->parent;
        else
          Parent=NULL;
      }else{
        if(current==Parent->left){
          //case 2 - right rotate Parent
          DEBUGMODE(std::cout << "Right Rotate on case 2: "<< Parent->key << '\n';)
          //can not change root addres
          rightRotate(Parent);
          current=current->right;
          DEBUGMODE(this->print();)
        }
        //case 3 - left rotate old grandParent new Parent
        DEBUGMODE(std::cout << "Left rotate on case 3: " << Parent->key << '\n';)
        leftRotate(Parent->parent);
        current->parent->color=0;
        if(current->parent->left->color!=-1) current->parent->left->color=1;
        if(current->parent->right->color!=-1) current->parent->right->color=1;
        //finished
        Parent=NULL;
      }
    }
    DEBUGMODE(std::cout << "Current: " << current->key << '\n';)
    DEBUGMODE(this->print();)
  }
  this->color=0;
}

template <class KEY, class DATA>
redBlackTree<KEY,DATA>::redBlackTree(){
  DEBUGMODE(std::cout << "New node created" << '\n';)
  color = -1; //Shows there is no data
  parent=NULL;
  left=NULL;
  right=NULL;
}

template <class KEY, class DATA>
redBlackTree<KEY,DATA>::~redBlackTree(){
  if(this->color!=-1){
    DEBUGMODE(std::cout << "Deleting left: "<< this->left->key << "-" << this->left->color << '\n';)
    delete this->left;
    DEBUGMODE(std::cout << "Deleting right: "<< this->right->key << "-" << this->right->color << '\n';)
    delete this->right;
  }
  DEBUGMODE(std::cout << "Deleted: "<< this->key << "-" << this->color << '\n';)
}

template <class KEY, class DATA>
void redBlackTree<KEY,DATA>::rightRotate(redBlackTree<KEY,DATA> *node){
  //can not change root addres
  KEY tmpKey;
  DATA tmpData;
  redBlackTree<KEY,DATA> * tmp;
  tmp=node->left;
  if(node==this){
    DEBUGMODE(std::cout << "Attempt to rotate with root" << '\n';)
    //swap key and data
    tmpData = this->data;
    tmpKey = this->key;
    this->data = tmp->data;
    this->key = tmp->key;
    tmp->data = tmpData;
    tmp->key = tmpKey;

    this->left=tmp->left;
    this->left->parent=this;
    tmp->left=tmp->right;
    tmp->right=this->right;
    tmp->right->parent=tmp;
    this->right=tmp;
  }else{
    DEBUGMODE(  std::cout << "Attempt to right rotate: " << node->key << ":" << node->color << "-" << tmp->key << ":" << tmp->color << '\n';)
    node->left=tmp->right;
    node->left->parent = node;
    tmp->right=node;
    tmp->parent=node->parent;
    node->parent->left == node ? node->parent->left=tmp : node->parent->right=tmp;
    node->parent=tmp;
  }
}

template <class KEY, class DATA>
void redBlackTree<KEY,DATA>::leftRotate(redBlackTree<KEY,DATA> *node){
  //can not change root addres
  KEY tmpKey;
  DATA tmpData;
  redBlackTree<KEY,DATA> * tmp;
  tmp=node->right;
  if(node==this){
    DEBUGMODE(std::cout << "Attempt to rotate with root" << '\n';)
    //swap key and data
    tmpData = this->data;
    tmpKey = this->key;
    this->data = tmp->data;
    this->key = tmp->key;
    tmp->data = tmpData;
    tmp->key = tmpKey;

    this->right=tmp->right;
    this->right->parent=this;
    tmp->right=tmp->left;
    tmp->left=this->left;
    tmp->left->parent=tmp;
    this->left=tmp;
  }else{
    DEBUGMODE(  std::cout << "Attempt to left rotate: " << node->key << "-" << tmp->key << '\n';)
    node->right=tmp->left;
    node->right->parent = node;
    tmp->left=node;
    tmp->parent=node->parent;
    node->parent->left == node ? node->parent->left=tmp : node->parent->right=tmp;
    node->parent=tmp;
  }
}

#endif
