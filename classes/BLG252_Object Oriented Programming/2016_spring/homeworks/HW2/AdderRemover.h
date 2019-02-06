#ifndef __ADDERREMOVER_H_INCLUDED__
#define __ADDERREMOVER_H_INCLUDED__

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

class node;
class ARTraverser;

#include "node.h"
#include "ARTraverser.h"
#include <string>

class AdderRemover
{
    public:
    	virtual void add(int)=0;
    	virtual void remove()=0;
    	virtual void setTraverser()=0;
    	void display() const;
    	void removeAll();
    	void traverse() const;
        void setName(std::string);
        std::string getName() const;

    protected:
    	node* head;
    	node* tail;
        std::string name;
    	int nodeCount;
    	ARTraverser* traverser;
};

#endif // ADDERREMOVER_H_INCLUDE
