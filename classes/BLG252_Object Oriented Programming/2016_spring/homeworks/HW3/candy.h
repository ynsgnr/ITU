#ifndef CANDY_H
#define CANDY_H

#include <string>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 09.05.2017
*/

class candy
{
public:
    candy();
    candy(const char* ,float ,float);
    candy(std::string ,float ,float);
    float number;
    float price;
    std::string name;
};

std::ostream& operator<<(std::ostream& os, const candy& s);

#endif // CANDY_H
