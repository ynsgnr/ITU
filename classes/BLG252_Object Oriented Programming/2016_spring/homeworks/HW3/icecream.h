#ifndef ICECREAM_H
#define ICECREAM_H

#include <string>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 09.05.2017
*/

class icecream
{
public:
    icecream();
    icecream(const char*,float , float);
    icecream(std::string ,float,float);
    float number;
    float price;
    std::string name;
};

std::ostream& operator<<(std::ostream& os, const icecream& s);

#endif // ICECREAM_H
