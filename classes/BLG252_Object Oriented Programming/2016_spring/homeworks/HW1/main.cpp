#include <iostream>
#include "SmallVector.h"

void printSmallVector(const char* const message, const SmallVector& in_vector) {
    std::cout << "Size:" << in_vector.getSize() <<" "<<message << ": "<<std::endl;
    for (int i = 0; i < in_vector.getSize(); i++){
        std::cout << in_vector[i] << " ";
    }
    std::cout<<std::endl;
    }

int main() {
    int temp[35];
    for (int i = 0; i < 35; i++){
        temp[i] = i;
    }

    SmallVector test(temp, 32); // Creating SmallVector with 10 elements
    // print test in reverse order
    int a[2]={2,3};
    test.push_back(a,2);
    printSmallVector("Printing test", test);
    printSmallVector("Printing test in reverse", test.reverse());

    SmallVector test2(temp, 35); // Creating SmallVector with 35 elements


    printSmallVector("Printing test 2", test2);
    printSmallVector("Printing test 2 in reverse", test2.reverse());

    SmallVector test6, test7;
    test7 = test6 = test2;
    test6.push_back(4);
    printSmallVector("Printing test 6", test6);
    test7[5]=10;
    test7.push_back(a,2);
    printSmallVector("Printing test 7", test7);

    SmallVector test3; // Empty SmallVector
    test3 = test2 + test; // Concatenate two SmallVectors

    printSmallVector("Printing test3", test3);

    SmallVector test4(test); // Copy SmallVector

    printSmallVector("Printing test4", test4);

    std::cout << "Popping last element of test4: "<<test4.pop_back()<<std::endl;
    printSmallVector("Printing test4", test4);
    std::cout << "Popping last element of test4: "<<test4.pop_back()<<std::endl;
    std::cout << "Popping last element of test4: "<<test4.pop_back()<<std::endl;
    std::cout << "Popping last element of test4: "<<test4.pop_back()<<std::endl;
    std::cout << "Popping last element of test4: "<<test4.pop_back()<<std::endl;
    printSmallVector("Printing test4", test4);

    SmallVector test5(temp, 2);

    printSmallVector("Printing test5-pure", test5);

    test5 = test5 * 5; // Replicate elements
     printSmallVector("Printing test5-replicated", test5);
    test5.push_back(12); // Add 12 at the end
     printSmallVector("Printing test5-replicated+12", test5);
    test5[0] = 4; // Modify the first element of test5
    printSmallVector("Printing test5-0=4", test5);
    std::cout << "Printing test5 in reverse: ";

    for (int i = 1; i < test5.getSize() + 1; i++){
        // Testing negative numbers as indices
        std::cout << test5[-i] << " ";
    }
    std::cout<<std::endl;
    std::cout << "Printing test5 overloaded from start: "<< test5[-125] <<std::endl;
    std::cout << "Printing test5 overloaded from end: "<<test5[125]<<std::endl;

    return 0;
}
