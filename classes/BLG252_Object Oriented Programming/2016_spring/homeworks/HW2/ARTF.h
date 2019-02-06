#ifndef __ARTF_H_INCLUDED__
#define __ARTF_H_INCLUDED__

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

class ARTraverser;

#include "ARTraverser.h"
class ARTF:public ARTraverser
{
    public:
        bool hasNode() const;
        int next();
        ~ARTF();
};


#endif // ARTF_H
