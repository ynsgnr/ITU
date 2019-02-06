/** 
 * C program to check whether a triangle is valid or not if its sides are given 
 */  
  
#include <stdio.h>
#include <math.h>
  
int main()  
{  
    int a, b, c; //a, b, c are three sides of a triangle  
  
    /* 
     * Reads all three sides of a triangle 
     */  
    printf("Enter three sides of triangle: \n");  
    scanf("%d %d %d", &a, &b, &c);  
  
    /* 
     * If a+b>c and a+c>b and b+c>a then triangle is valid 
     */  
    if(( abs(a-b) < c < a+b ) && (abs(a-c) < b < a+c) && (abs(b-c) < a < b+c))
    {  
        printf("\nTriangle is valid");  
    }  
    else
    {  
        printf("\nTriangle is not valid");  
    }  
  
    return 0;  
} 