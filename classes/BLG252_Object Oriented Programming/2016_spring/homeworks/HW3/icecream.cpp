#include "icecream.h"

icecream::icecream(const char* n,float l, float p)
{
    name=std::string(n);
    number=l;
    price=p;
}

icecream::icecream(std::string n,float w,float p)
{
    name=n;
    number=w;
    price=p;
}

icecream::icecream(){

}

std::ostream& operator<<(std::ostream& os, const icecream& s)
{
    os<<std::to_string(s.number)<<std::string("-")<<s.name;
    return os;
}
