#include "ARTL.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 23.04.2017
*/

bool ARTL::hasNode() const{
    return current!=nullptr;
}

int ARTL::next(){
    if(ARTL::hasNode()){
        int tmp=current->getData();
        current=current->getPrev();
		return tmp;
    }else{
        return -1;
	}
}

ARTL::~ARTL()
    {}
