#ifndef SHOP_H
#define SHOP_H

#include <list>
#include <iostream>
#include <iterator>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 09.05.2017
*/

template <class D> class node{
public:
    D data;
    node* next;
    node();
};

template <class D> class shop{
public:
    shop();
    shop(D);
    void add(D);
    void add(D*);
    D operator[](int) const;
    void setDiscount(float d);
    float getDiscount() const;
    int getSize() const;
    ~shop();
    shop(const shop<D>&);
private:
    float discount;
    node<D>* head;
    node<D>* tail;
    int size=0;
};

#include "shop.cpp"

#endif // SHOP_H
