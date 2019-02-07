#ifndef __FAFR_H_INCLUDED__
#define __FAFR_H_INCLUDED__

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

class AdderRemover;

#include "AdderRemover.h"

class FAFR:public AdderRemover
{
    public:
        void add(int);
        void remove();
        void setTraverser();
        FAFR();
        ~FAFR();
};

#endif // FAFR_H