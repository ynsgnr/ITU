#ifndef SHOP_CPP
#define SHOP_CPP

#include "shop.h"

#include <list>
#include <iterator>
#include <iostream>

template <class D> node<D>::node(){

}

template <class D> shop<D>::shop()
{
    head=nullptr;
    tail=nullptr;
}

template <class D> shop<D>::shop(D dessert)
{
    head = new node<D>;
    head->data=dessert;
    head->next=head;
    tail=head;
    size++;
}

template <class D> void shop<D>::add(D dessert){
    if(size==0){
        //first element
        head = new node<D>;
        head->data=dessert;
        head->next=head;
        tail=head;
    }
    else{
        node<D> * tmp = tail;
        tail=new node<D>;
        tail->data=dessert;
        tail->next=nullptr;
        tmp->next=tail;
    }
    size++;
}

template <class D> void shop<D>::add(D* dessert){
    if(size==0){
        //first element
        head = new node<D>;
        head->data=*dessert;
        head->next=head;
        tail=head;
    }
    else{
        node<D> * tmp = tail;
        tail=new node<D>;
        tail->data=*dessert;
        tail->next=nullptr;
        tmp->next=tail;
    }
    size++;
}

template <class D> D shop<D>::operator[](int i) const{
    if(size<=i)throw "Out of range";
    node<D>* tmp=head;
    for(int j=0;j<i;j++){
        tmp=tmp->next;
    }
    return tmp->data;
}

template <class D> void shop<D>::setDiscount(float d){
    if(d>30 || d<0) throw "invalid value";
    discount=d;
}

template <class D> float shop<D>::getDiscount() const{
   return discount;
}

template <class D> int shop<D>::getSize() const{
    return size;
}

template <class D> shop<D>::~shop(){
   node<D>* tmp;
    while(head!=tail){
        tmp=head->next;
        delete head;
        head=tmp;
    }
    delete head;
}

template <class D> std::ostream& operator<<(std::ostream& os, const shop<D>& s)
{
    os<<"**********************"<<std::endl<<"Number of items:"<<s.getSize()<<std::endl;
    float cost=0;
    float totalCost=0;
    for(int i=1;i<=s.getSize();i++){
        cost=(float)s[i-1].number*(float)s[i-1].price;
        os<<i<<". "<<s[i-1].name<<" #"<<s[i-1].number<<" Cost: "<<cost<<std::endl;
        totalCost=totalCost+(float)cost;
    }
    os<<"**********************"<<std::endl<<"Total cost: "<<totalCost<<std::endl<<"**********************"<<std::endl;
    return os;
}

#endif//Because its a template class
