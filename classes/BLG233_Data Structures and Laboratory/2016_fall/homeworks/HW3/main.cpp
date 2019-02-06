#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 18.12.2016
*/

struct item
{
    string data;
    item * prev;//Linked list
};

//Queue
    item* front;
    item* back;

//Stack
    item* head;

int atoi(char *);//string to int
bool stringToStack(string);//convert to postfix
bool solve(int*);//solve stack return result
void enqueue(int);//Convert int to string and add to queue
void close();//Clear memory and print answer queue
int getElements(char * prefix, int position,int end);//get all the elements possible returns number of elements
void push(string data);//Push data to stack

int main(int argc, char* argv[])
{
    cout<<"Initializing the interpreter..."<<endl;

    //Intilize queue
    item * tmp=new item;
    front=tmp;
    back=tmp;

    //Intilize stack
    head=NULL;

    string line;
    int answer;

    if(argc<2){
        //get input from user
        while(line!="exit"){

                //clear stack
                while(head!=NULL){
                    tmp=head->prev;
                    delete head;
                    head=tmp;
                }

                cout<<">>";
                getline(cin,line);
                if(stringToStack(line) || solve(&answer))
                    cout<<"Syntax error"<<endl;
                else {
                    //print Postfix String
                    cout<<"Postfix string: ";
                    tmp=head;
                    while(head!=NULL){
                        cout<< head->data<<" ";
                        head=head->prev;
                    }
                    head=tmp;
                    enqueue(answer);
                    cout<<"Answer: "<<answer<<endl;
                }
        }
    }
    else{
        //get input from file
        for(int i=1;i<argc;i++){
            ifstream file (argv[i-1]);
            //clear stack
            while(head!=NULL){
                tmp=head->prev;
                delete head;
                head=tmp;
            }
            if (file.is_open())
            {
                while(file.good()){
                    getline(file,line);
                    if(stringToStack(line) || solve(&answer))
                        cout<<"syntax error on line: "<<line<<endl;
                    else{
                        enqueue(answer);
                    }
                }
                file.close();
            }
            else cout << "Unable to read file: "<<argv[i-1]<<endl;
        }
    }
    close();

    return 0;
}

bool stringToStack(string line){
    int position=0;
    char prefix[line.length()+1];
    strcpy(prefix,line.c_str());
    string tmp;
    int temp;
    //convert to postfix
    /*
    Unary
    ans
    inf
    -inf

    abs
    sqrt

    Binary
    div
    sub

    Unary/Binary
    exp a    e^a
    exp a b  a^b
    log n    dogal logaritma
    log x n
    mod n    mod 10
    mod x n  n mod x

    Polynary
    sum
    product
    min
    max
    */
    if(!line.compare(position,4,"abs ")){
        push("abs");
        position=position+4;
        if(getElements(prefix,position,line.length())!=1)return true;
    }
    else if(!line.compare(position,5,"sqrt ")){
        push("sqrt");
        position=position+5;
        if(getElements(prefix,position,line.length())!=1)return true;
    }
    else if(!line.compare(position,4,"div ")){
        push("div");
        position=position+4;
        if(getElements(prefix,position,line.length())!=2)return true;
    }
    else if(!line.compare(position,4,"sub ")){
        push("sub");
        position=position+4;
        if(getElements(prefix,position,line.length())!=2)return true;
    }
    else if(!line.compare(position,4,"exp ")){
        push("exp");
        position=position+4;
        temp=getElements(prefix,position,line.length());
        if(temp!=1 && temp!=2)return true;
    }
    else if(!line.compare(position,4,"log ")){
        push("log");
        position=position+4;
        temp=getElements(prefix,position,line.length());
        if(temp!=1 && temp!=2)return true;
    }
    else if(!line.compare(position,4,"mod ")){
        push("mod");
        position=position+4;
        temp=getElements(prefix,position,line.length());
        if(temp!=1 && temp!=2)return true;
    }
    else if(!line.compare(position,4,"sum ")){
        push("sum");
        position=position+4;
        if(getElements(prefix,position,line.length())<1)return true;
    }
    else if(!line.compare(position,8,"product ")){
        push("product");
        position=position+8;
        if(getElements(prefix,position,line.length())<1)return true;
    }
    else if(!line.compare(position,4,"min ")){
        push("min");
        position=position+4;
        if(getElements(prefix,position,line.length())<1)return true;
    }
    else if(!line.compare(position,4,"max ")){
        push("max");
        position=position+4;
        if(getElements(prefix,position,line.length())<1)return true;
    }
    else{
        return true;
    }

    return false;
}

int getElements(char * prefix, int position,int end){
    string tmp;
    int elementsFound=0;

    end--;//pass null character

    while(position<=end){
        tmp.clear();
        elementsFound++;
        if((prefix[end]>='0' && prefix[end]<='9')){
            //there is a number
            while((prefix[end]>='0' && prefix[end]<='9') && position<=end){
                //get numbers
                tmp=prefix[end]+tmp;
                end--;
            }
            //get minus
            if(prefix[end]=='-'){
                tmp="-"+tmp;
                end--;
            }
            if(end>=(position-1) && prefix[end]==' ')push(tmp);
            else return -1;
            end--;
        }
        else if(prefix[end]==')'){
            //get paranthesis
            push(")");
            tmp.clear();
            end-=2;
            while(prefix[end]!='(' && position<=end){
                tmp=prefix[end]+tmp;
                end--;
            }
            tmp.erase (tmp.begin());//remove unnecessary space
            if(stringToStack(tmp)) return -1;
            push("(");
            end--;
            if(prefix[end]!=' ') return -1;
            end--;
        }
        else if(prefix[end]==' ' || position==end){
            push(tmp);
            end--;
        }
        else return -1;
    }
    return elementsFound;
}

bool solve(int* answer){
    item* tmp;
    long result;
    int numberCount=0;
    long numbers[50];
    //solve stack return result

    /*while(head!=NULL){
        tmpString=head->data;
        if(!tmpString.compare(position,3,"abs")){
            numbers[numberCount]=(long)abs(numbers[numberCount]);
            numberCount++;
        }
        else if(!tmpString.compare(position,4,"sqrt")){
            numbers[numberCount]=(long) sqrt(numbers[numberCount]);
            numberCount++;
        }
        else if(!tmpString.compare(position,3,"div")){

        }
        else if(!tmpString.compare(position,3,"sub")){

        }
        else if(!tmpString.compare(position,3,"exp")){

        }
        else if(!tmpString.compare(position,3,"log")){

        }
        else if(!tmpString.compare(position,3,"mod")){

        }
        else if(!tmpString.compare(position,3,"sum")){

        }
        else if(!tmpString.compare(position,7,"product")){

        }
        else if(!tmpString.compare(position,3,"min")){

        }
        else if(!tmpString.compare(position,3,"max")){

        }
        else{
            //number
            numbers[numberCount]= (long) atoll(temp->data.c_str);
            numberCount++;
        }

        tmp=head;
        head=head->prev;
        delete tmp;
    }

    return false;

*/
    *answer=result;
    return false;
}

void push(string data){
    item* tmp=new item;
    tmp->data=data;
    tmp->prev=head;
    head=tmp;
}

void enqueue(int answer){
    item* tmp=new item;

    //convert to string
    stringstream  ss;
    ss<<answer;
    tmp->data=ss.str();

    //enqueue
    back->prev=tmp;
    tmp->prev=NULL;
    back=tmp;
}

void close(){
    item* tmp;
    //clear stack
    while(head!=NULL){
        tmp=head->prev;
        cout<<head->data<<" ";
        delete head;
        head=tmp;
    }

    //print and delete queue
    if(front!=NULL)
        cout<<front->data;
    while(front!=back){
        tmp=front;
        front=front->prev;
        delete tmp;
        cout<<"->"<<front->data<<endl;
    }
    delete back;
}
