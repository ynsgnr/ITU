#ifndef SMALLVECTOR_H
#define SMALLVECTOR_H

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 27.03.2017
*/

class SmallVector
{
    public:
        //Constructors:
        SmallVector();
        SmallVector(int*,int);
        SmallVector(const SmallVector&);

        int getSize() const;//Returns total size of vector
        int pop_back();//Pop last element from vector
        void push_back(int);//Add an element
        void push_back(int* ,int );//Add an array
        SmallVector reverse() const;//Returns reverse of the vector

        //Operator overrides:
        int& operator[](int);
        int operator[](int) const;
        const SmallVector& operator=(const SmallVector &);
        SmallVector operator+(const SmallVector& rightSide) const;
        SmallVector operator*(const int& rightSide) const;

        virtual ~SmallVector();

    protected:

    private:
        const int STATIC_SIZE=32;//Total size of staticBuffer
        int staticBuffer[32];//Static array of vector
        int* dynamicBuffer;//Dynamic array of vector
        int vectorSize; //Acts as an indicator (Starts from 0)
        void shrink(int);//Shrinks vector's avaliable space if dynamic array is in use
        void expand(int);//Expands vector's avaliable space if dynamic array is in use
};

#endif // SMALLVECTOR_H
