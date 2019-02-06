#ifndef __LALR_H_INCLUDED__
#define __LALR_H_INCLUDED__

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

class AdderRemover;

#include "AdderRemover.h"

class LALR:public AdderRemover
{
    public:
        void add(int);
        void remove();
        void setTraverser();
        LALR();
        ~LALR();
};

#endif // LALR_H
