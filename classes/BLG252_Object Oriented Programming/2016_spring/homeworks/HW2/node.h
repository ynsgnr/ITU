#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

class node
{
    public:
        int getData() const;
        node* getNext() const;
        node* getPrev() const;
        node();
        node(node* tmp,int tmpD);
        node(int tmpD,node* tmp);
        void setData(int tmp);
        void setNext(node* tmp);
        void setPrev(node* tmp);

    private:
        int data;
        node* next;
        node* prev;
};

#endif // NODE_H
