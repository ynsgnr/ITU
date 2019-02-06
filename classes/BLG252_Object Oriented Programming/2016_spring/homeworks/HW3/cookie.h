#ifndef COOKIE_H
#define COOKIE_H

#include <string>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 09.05.2017
*/

class cookie
{
public:
    cookie();
    cookie(const char* , int , float);
    cookie(const char* , float , float);
    cookie(std::string , float , float);
    int number;
    float price;
    std::string name;
};

std::ostream& operator<<(std::ostream& os, const cookie& s);

#endif // COOKIE_H
