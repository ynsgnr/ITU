#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "shop.h"
#include "candy.h"
#include "cookie.h"
#include "icecream.h"

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* compiled with command:
* g++ -std=c++11 main.cpp icecream.cpp cookie.cpp candy.cpp shop.cpp
* Date: 09.05.2017
*/


int main() {

    std::ofstream output;
    output.open ("output.txt");

    cookie cookie1("Chocolate Chip Cookies",10, 180); //(name, pieces, priceperdozen)
    cookie cookie2("Cake Mix Cookies", 16, 210);

    shop<cookie> cookieShop(cookie1);
    cookieShop.add(cookie2);
    output<<cookieShop<<"\n";

    try{
        output<<cookieShop[2];
    }
    catch(const char* msg){
        output<<msg<<"\n";
    }

    try{
        cookieShop.setDiscount(10);
    }
    catch(const char* msg){
        output<<msg<<"\n";
    }

    icecream icecream1("Chocolate ice cream",1.5, 170); //(name, litre, priceperlitre)
    shop<icecream> icecreamShop(icecream1);
    output<<icecreamShop<<"\n";

    try{
    icecreamShop.setDiscount(50);
    }
    catch(const char* msg){
        output<<msg<<"\n";
    }

    candy candy2("Gummi bears",12,89); //(name, weight, priceperkg)
    candy candy3("Hanukkah gelt",8,110);

    shop<candy> candyShop(candy2);
    candyShop.add(candy3);

    candyShop.setDiscount(15);
    output<<candyShop<<"\n";

    std::string line;
    std::string name;
    char type;
    float number;
    float price;
    std::string tmp;

    shop<cookie> cookieStock;
    shop<icecream> icecreamStock;
    shop<candy> candyStock;


    std::ifstream stock;
    stock.open ("stock.txt");
    if (stock.is_open()){
        getline(stock,line);//ignore first line

        while (!stock.eof()){
            getline(stock,line);

            //process string
            name=line.substr(0, line.find("\t"));
            type=*(line.substr(line.find("\t")+1,1).c_str());
            tmp=line.substr(line.find("\t")+1,line.size());
            tmp=tmp.substr(tmp.find("\t")+1,line.find_last_of("\t"));
            //get numbers
            number=std::stof(tmp);
            price=std::stof(line.substr(line.find_last_of("\t",line.size())));//get price betweem last tab and end of line

            if(type=='1'){
                cookieStock.add(new cookie(name,number,price));
            }else if(type=='2'){
                icecreamStock.add(new icecream(name,number,price));
            }else if(type=='3'){
                candyStock.add(new candy(name,number,price));
            }
            else{
                std::cout<<"Error in stock file on line:"<<"\n"<<line<<"\n";
            }
        }
    }
    else{
        std::cout<<"Error in reading file!"<<"\n";
    }
    stock.close();

    std::cout<<"Stock we have:"<<"\n";
    std::cout<<cookieStock<<"\n";
    std::cout<<icecreamStock<<"\n";
    std::cout<<candyStock<<"\n";

    output<<cookieStock<<"\n";
    output<<icecreamStock<<"\n";
    output<<candyStock<<"\n";

    std::cout<<"Order we got:"<<"\n";

    float Tcost;
    float discount=10;
    bool keepGoing=true;
    int i;

    std::ifstream order;
    order.open ("order.txt");
    if (order.is_open()){
        getline(order,line);
        while (!order.eof()){
            //process string
            name=line.substr(0, line.find("\t"));
            type=*(line.substr(line.find("\t")+1,1).c_str());
            tmp=line.substr(line.find("\t")+1,line.size());
            tmp=tmp.substr(tmp.find("\t")+1,line.find_last_of("\t"));
            //get numbers
            number=std::stof(tmp);
            keepGoing=true;
            i=0;
            if(type=='1'){
                while(i<cookieStock.getSize() && keepGoing){
                    if(cookieStock[i].name==name){
                        keepGoing=false;//quit loop
                        if(cookieStock[i].number>=number){
                            std::cout<<number<<" "<<name<<"-Cost:"<<(cookieStock[i].price*number)<<"\n";
                            Tcost=Tcost+(cookieStock[i].price*number);
                        }
                        else{
                            std::cout<<"We dont have enough cookies! "<<cookieStock[i].number<<"-"<<number<<"\n";
                        }
                    }
                    i++;
                }
            }else if(type=='2'){
                 while(i<cookieStock.getSize() && keepGoing){
                    if(icecreamStock[i].name==name){
                        keepGoing=false;//quit loop
                        if(icecreamStock[i].number>=number){
                            std::cout<<number<<" "<<name<<"-Cost:"<<(icecreamStock[i].price*number)<<"\n";
                            Tcost=Tcost+(icecreamStock[i].price*number);
                        }
                        else{
                            std::cout<<"We dont have enough cookies!"<<"\n";
                        }
                    }
                    i++;
                }
            }else if(type=='3'){
                 while(i<cookieStock.getSize() && keepGoing){
                    if(candyStock[i].name==name){
                       keepGoing=false;//quit loop
                        if(candyStock[i].number>=number){
                            std::cout<<number<<" "<<name<<"-Cost:"<<(candyStock[i].price*number)<<"\n";
                            Tcost=Tcost+(candyStock[i].price*number);
                        }
                        else{
                            std::cout<<"We dont have enough cookies!"<<"\n";
                        }
                    }
                    i++;
                }
            }
            else{
                std::cout<<"Error in order file on line:"<<"\n"<<line<<"\n";
            }
            getline(order,line);
        }
    }
    else{
        std::cout<<"Error in reading file!"<<"\n";
    }
    order.close();

    output<<"Total cost: "<<Tcost<<"\n";
    output<<"Discount: "<<discount<<"\n";
    output<<"Discount amount: -"<<((Tcost*discount)/100)<<"\n";
    output<<"Discounted cost: "<<(Tcost-((Tcost*discount)/100))<<"\n";
    output<<"**********************";
    output.close();

    std::cout<<"Output completed"<<"\n";

}