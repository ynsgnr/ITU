#include "candy.h"
#include <string>

candy::candy(const char* n,float w,float p)
{
    name=std::string(n);
    number=w;
    price=p;
}

candy::candy(std::string n,float w,float p)
{
    name=n;
    number=w;
    price=p;
}


candy::candy(){

}

std::ostream& operator<<(std::ostream& os, const candy& s)
{
    os<<std::to_string(s.number)<<std::string("-")<<s.name;
    return os;
}