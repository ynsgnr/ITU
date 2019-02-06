#include "cookie.h"
#include <string>

#define dozen 12

cookie::cookie(const char* n, int pieces, float p)
{
    name=std::string(n);
    number=pieces;
    price=p/dozen;
}

cookie::cookie(const char* n, float pieces, float p)
{
    name=std::string(n);
    number=pieces;
    price=p/dozen;
}


cookie::cookie(std::string n,float w,float p)
{
    name=n;
    number=w;
    price=p/dozen;
}

cookie::cookie(){

}

std::ostream& operator<<(std::ostream& os, const cookie& s)
{
    os<<std::to_string(s.number)<<std::string("-")<<s.name;
    return os;
}
