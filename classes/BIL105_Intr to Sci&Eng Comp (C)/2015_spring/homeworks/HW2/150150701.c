/** @file BIL105 Spring 2016 HomeWork 1
*
* A program that produces random numbers by two different
* methods. First method is MID-PRNG and the second one is
* LSD-PRNG. User chooses one of the methods the create number.
*
* @author
*
* Name:             Yunus GÃ¼ngÃ¶r
*
* Student no:       150150701
*
* Date:             09/04/2016
*
* E-Mail:           yunusgnr@gmail.com
*
* Tested on: (ITU SSH Server)
*
* Compiler:		GCC 4.8.5 20150623
*
* Operating System: Red Hat 4.8.5-4
*
* IDE:		None
*
* Operating System: Linux Red Hat 4.8.5-4
*/

#include <stdio.h>
#include <stdlib.h>

void mid_rng(long *number);
void lsd_rng(long *number);
void take_samples (int whichRNG,int *range1,int *range2,int *range3,int *range4,int *range5);
void draw_histogram (int *range1,int *range2,int *range3,int *range4,int *range5);
void map(int number, int *range1,int *range2,int *range3,int *range4,int *range5);

int main ()
{
	int whichRNG /* determines which algortihym to use*/;
	int range1=0 ,range2=0 ,range3=0 ,range4=0 ,range5=0;//stores mapped data.
	int i;
	do
	{
		printf("Which PRNG Algorithm?\n	1.MID-PNRG\n	2.LSD-PNRG\n");
		scanf("%d",&whichRNG);
	}
	while(whichRNG!=1 && whichRNG!=2);
	take_samples(whichRNG,&range1,&range2,&range3,&range4,&range5); //get input and create random variables
	draw_histogram(&range1,&range2,&range3,&range4,&range5);
	return 0;
}

/*creates random variable by mid-rng
	MID-RNG:
   take the square of number,
   Pick out the  middle five digits of the square as a random number
*/
void mid_rng(long *number) //creates random variable by mid-rng
{
	long long square;
	square=(*number)*(*number);
	if (square<1000000000) //square has 9 digits
		*number=(square/100)%100000; //skip first two digits and take the following five digit
	else //square has 10 digits
		*number=(square/1000)%100000; //skip first three digits and take the following five digits
	return;
}

/*creates random variable by lsd-rng
	LSD-RNG:
   multiply the number with 73 to get a product. 
   Pick out the low-order five digits of the product as a random number. 
*/
void lsd_rng(long *number) 
{
	long long product;
	product=(*number)*73;
	*number=product%100000; //get low-order five digits
	return;
}

/*Creates random numbers based on desired method*/
void take_samples(int whichRNG,int *range1,int *range2,int *range3,int *range4,int *range5)
{
	int i,num_samples;
	long number;
	if(whichRNG==1)//mid-rng
	{
		do
		{
			printf("Enter the seed:");
			scanf("%li",&number);
		}
		while(number<10000 || number>99999); //check if seed has 5 digits or not
		printf("Enter the Number of Samples:");	
		scanf("%d",&num_samples);
		for(i=0;i<num_samples;i++)
		{
			mid_rng(&number);
			map(number%500,range1,range2,range3,range4,range5);
		}
	}
	else //lsd-rng
	{
		do
		{
			printf("Enter the seed:");
			scanf("%li",&number);
		}
		while(number<10000 || number>99999 || number%2==0 || number%5==0); //check if seed has 5 digits and its odd and does not end with '5'
		printf("Enter the Number of Samples:");	
		scanf("%d",&num_samples);
		for(i=0;i<num_samples;i++)
		{
			lsd_rng(&number);
			map(number%500,range1,range2,range3,range4,range5);
		}
	}
	return;
}

/** Draws histogram based on range array on the screen
*/
void draw_histogram (int *range1,int *range2,int *range3,int *range4,int *range5)
{
	int i,sum;
	sum=*range1+*range2+*range3+*range4+*range5;
	*range1=(float)*range1/sum*100;
	printf("0...100");
	for(i=0;i<*range1;i++)
		printf("*");
	printf("(%%");
	printf("%d)\n",*range1);

	*range2=(float)*range2/sum*100;
	printf("101..200");
	for(i=0;i<*range2;i++)
		printf("*");
	printf("(%%");
	printf("%d)\n",*range2);

	*range3=(float)*range3/sum*100;
	printf("201...130");
	for(i=0;i<*range3;i++)
		printf("*");
	printf("(%%");
	printf("%d)\n",*range3);

	*range4=(float)*range4/sum*100;
	printf("301...400");
	for(i=0;i<*range4;i++)
		printf("*");
	printf("(%%");
	printf("%d)\n",*range4);

	*range5=(float)*range5/sum*100;
	printf("401...500");
	for(i=0;i<*range5;i++)
		printf("*");
	printf("(%%");
	printf("%d)\n",*range5);

	return;
}

/**		maps number such as
		range1=1..100,
		range2=101..200,
		range3=201..300,
		range4=301..400,
		and range5=401..500
*/

void map(int number,int* range1,int* range2,int* range3,int* range4,int* range5)
{
	if(number<=100)
		*range1+=1;
	else if(number<=200)
		*range2+=1;
	else if(number<=300)
		*range3+=1;
	else if(number<=400)
		*range4+=1;
	else if(number<=500)
		*range5+=1;
	return;
}