#ifndef __ARTRAVERSER_H_INCLUDE__
#define __ARTRAVERSER_H_INCLUDE__

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

class node;

#include "node.h"

class ARTraverser
{
    public:
        virtual bool hasNode() const=0;
        virtual int next()=0;
        node* current;
        ARTraverser();
        virtual ~ARTraverser(){};
};

#endif // ARTRAVERSER_H
