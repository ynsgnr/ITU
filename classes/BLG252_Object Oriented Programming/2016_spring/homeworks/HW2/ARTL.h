#ifndef __ARTL_H_INCLUDED__
#define __ARTL_H_INCLUDED__

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

class ARTraverser;

#include "ARTraverser.h"
class ARTL:public ARTraverser
{
    public:
    	bool hasNode() const;
        int next();
        ~ARTL();
};

#endif // ARTRAVERSER_H
