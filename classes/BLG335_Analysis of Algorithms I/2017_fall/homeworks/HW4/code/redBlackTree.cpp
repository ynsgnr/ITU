#ifdef DEBUG
#define DEBUGMODE(code) code
#else
#define DEBUGMODE(code)
#endif

#ifdef AUGMENT
#define AUGMENTED(code) code
#else
#define AUGMENTED(code)
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
  std::cout<<key<<"-"<<gender<<"-";
  std::cout<<data;
  DEBUGMODE(std::cout << " Man#: " << num_man << "-Woman#: "<< num_woman;)
  std::cout<<std::endl;
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
    std::cout<<node->key<<"-"<<node->gender<<"-";
    std::cout<<node->data;
    DEBUGMODE(std::cout << " Man#: " << node->num_man << "-Woman#: "<< node->num_woman;)
    std::cout<<std::endl;

    printNode(node->right,height+1);
  }
}

template <class KEY, class DATA>
void redBlackTree<KEY,DATA>::insert(KEY key,char Gender,DATA data){
  redBlackTree<KEY,DATA> * current;
  current=this;
  DEBUGMODE(std::cout << "Adding key: " << key << " has gender: " << gender << '\n';)
  while(current->color!=-1){
    if(current->key>key){
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

  //Augmenting:
  current->gender=Gender;
  if(current->gender=='M'){
    current->num_man=1;
    while(Parent!=NULL){
      Parent->num_man+=1;
      Parent=Parent->parent;
    }
  }else{
    current->num_woman=1;
    while(Parent!=NULL){
      Parent->num_woman+=1;
      Parent=Parent->parent;
    }
  }
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
  num_man=0;
  num_woman=0;
  gender='F';
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
  int tmpCount;
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

    //Augmenting
    tmp->num_man=tmp->left->num_man+tmp->right->num_man;
    tmp->num_woman=tmp->left->num_woman+tmp->right->num_woman;
    tmp->gender=='M' ? tmp->num_man+=1 : tmp->num_woman+=1;
    this->num_man=this->left->num_man+this->right->num_man;
    this->num_woman=this->left->num_woman+this->right->num_man;
    this->gender=='M' ? this->num_man+=1 : this->num_woman+=1;

  }else{
    DEBUGMODE(  std::cout << "Attempt to right rotate: " << node->key << ":" << node->color << "-" << tmp->key << ":" << tmp->color << '\n';)
    node->left=tmp->right;
    node->left->parent = node;
    tmp->right=node;
    tmp->parent=node->parent;
    node->parent->left == node ? node->parent->left=tmp : node->parent->right=tmp;
    node->parent=tmp;

    //Augmenting
    node->num_man=node->left->num_man+node->right->num_man;
    node->num_woman=node->left->num_woman+node->right->num_man;
    node->gender=='M' ? node->num_man+=1 : node->num_woman+=1;
    tmp->num_man=tmp->left->num_man+tmp->right->num_man;
    tmp->num_woman=tmp->left->num_woman+tmp->right->num_woman;
    tmp->gender=='M' ? tmp->num_man+=1 : tmp->num_woman+=1;

  }
}

template <class KEY, class DATA>
void redBlackTree<KEY,DATA>::leftRotate(redBlackTree<KEY,DATA> *node){
  //can not change root addres
  KEY tmpKey;
  DATA tmpData;
  char tmpGender;
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
    tmpGender = tmp->gender;
    tmp->gender = this->gender;
    this->gender = tmpGender;

    this->right=tmp->right;
    this->right->parent=this;
    tmp->right=tmp->left;
    tmp->left=this->left;
    tmp->left->parent=tmp;
    this->left=tmp;

    //Augmenting
    tmp->num_man=tmp->left->num_man+tmp->right->num_man;
    tmp->num_woman=tmp->left->num_woman+tmp->right->num_woman;
    tmp->gender=='M' ? tmp->num_man+=1 : tmp->num_woman+=1;
    this->num_man=this->left->num_man+this->right->num_man;
    this->num_woman=this->left->num_woman+this->right->num_man;
    this->gender=='M' ? this->num_man+=1 : this->num_woman+=1;

  }else{
    DEBUGMODE(  std::cout << "Attempt to left rotate: " << node->key << "-" << tmp->key << '\n';)
    node->right=tmp->left;
    node->right->parent = node;
    tmp->left=node;
    tmp->parent=node->parent;
    node->parent->left == node ? node->parent->left=tmp : node->parent->right=tmp;
    node->parent=tmp;

    //Augmenting
    node->num_man=node->left->num_man+node->right->num_man;
    node->num_woman=node->left->num_woman+node->right->num_man;
    node->gender=='M' ? node->num_man+=1 : node->num_woman+=1;
    tmp->num_man=tmp->left->num_man+tmp->right->num_man;
    tmp->num_woman=tmp->left->num_woman+tmp->right->num_woman;
    tmp->gender=='M' ? tmp->num_man+=1 : tmp->num_woman+=1;

  }
}

//Augmenting
template <class KEY, class DATA>
KEY redBlackTree<KEY,DATA>::findWomanOnOrder(int i,redBlackTree<KEY,DATA>* n){
  //find ith woman
  redBlackTree<KEY,DATA>* node;
  int r;
  if(n==NULL)
    node=this;
  else
    node=n;

  if(node->color==-1)return NULL; //Not enough element

  r=(node->left->num_woman);
  if(node->gender=='F')
    r+=1;
  if(r==i && node->gender=='F') return node->key;
  else if(i<r  || r==i) return findWomanOnOrder(i,node->left);
  else return findWomanOnOrder(i-r,node->right);
}

template <class KEY, class DATA>
KEY redBlackTree<KEY,DATA>::findManOnOrder(int i,redBlackTree<KEY,DATA>* n){
  //find ith man
  redBlackTree<KEY,DATA>* node;
  int r;
  if(n==NULL)
    node=this;
  else
    node=n;

  if(node->color==-1) return NULL; //Not enough element

  r=(node->left->num_man);
  if(node->gender=='M')
    r+=1;
  if(r==i && node->gender=='M') return node->key;
  else if(i<r || r==i) return findManOnOrder(i,node->left);
  else return findManOnOrder(i-r,node->right);
}

#endif
