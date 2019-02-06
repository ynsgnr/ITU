#include<stdio.h>
int main(){

  int i,j,s,temp,array[10];

  //get total number of elements from user
  printf("Enter total elements: ");
  scanf("%d",&s);

  //get elements from the user
  printf("Enter %d elements: ",s);
  for(i=0;i<s;i++)
      scanf("%d",&array[i]);
  

  // sort the array
	  for(i=1;i<s;i++){
      temp=array[i];
      j=i-1;
      while((temp<array[j])&&(j>=0)){
      array[j+1]=array[j];
          j=j-1;
      }
      array[j+1]=temp;
  }
  

  // print sorted array
  printf("After sorting: ");
  for(i=0;i<s;i++)
      printf(" %d",array[i]);

  return 0;
}