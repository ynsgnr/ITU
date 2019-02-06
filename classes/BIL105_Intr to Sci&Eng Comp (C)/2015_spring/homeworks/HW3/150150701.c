/** @file BIL105 Spring 2016 HomeWork 3
*
* A program that performs string processes
*
* @author
*
* Name:             Yunus Gungor
*
* Student no:       150150701
*
* Date:             01/05/2016
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
#include <string.h>

int user_menu();
int set_ccs(char**);
char *sub_string (char *ccs, int begin_index, int end_index);
char *remove_string(char **ccs, int begin_index, int end_index);
int insert_string(char **ccs, char *insert, int begin_index);
int replace_string(char **ccs, char *find, char *replace);
int findLeght(char* str);

int main(){
	int i,keepGoing=1,lenght,begin_index,end_index;
	char *ccs,*p;
	p=malloc(sizeof(char));//To cancel segmantation errors
	if (!p)
	{
		printf("Error:Not enough space on memory!\n");
		return -1;
	}
	else
	{
		ccs=p;
		*ccs='\0';//its null because ccs is not entered by user
	}
	while(keepGoing)
	{
		switch (user_menu())//print menu
		{
		case 0:
			keepGoing=0;//exit program
			break;
		case 1://get ccs
			set_ccs(&ccs);
			break;
		case 2://print a part from ccs
			if (*ccs)//detect if ccs entered or not
			{
				/*get begin and end index*/
				int begin_index,end_index;
				printf("Enter the BEGIN INDEX and END INDEX numbers:\n");
				scanf("%d %d",&begin_index,&end_index);
				p=sub_string (ccs,begin_index,end_index);//get substring
				if (p)
					printf("Substring(%d,%d):%s\n",begin_index,end_index,p);
				else
					printf("An error happened!\n");
			}
			else
			{
				printf("Error:CCS must be entered to perform this action!\n");	
			}
			break;
		case 3://Remove a part from ccs
			if (*ccs)//detect if ccs entered or not
			{
				/*get begin and end index*/
				printf("Enter the BEGIN INDEX and END INDEX numbers:\n");
				scanf("%d %d",&begin_index,&end_index);
				p=remove_string(&ccs,begin_index,end_index);
				if (p)
					printf("Removed String(%d,%d)%s\n",begin_index,end_index,p);
				else
					printf("An error happened!\n");
			}
			else
			{
				printf("Error:CCS must be entered to perform this action!\n");
			}
			break;
		case 4://insert into ccs
			if (*ccs)//detect if ccs entered or not
			{
				
				char * insert;
				int i=0;
				//get string to insert
				p=malloc(sizeof(char)*80);
				if (!p)
				{
					printf("Error:Not enough space on memory!\n");
					return -1;
				}
				else
				{
					insert=p;
				}
				printf("Enter a new string for insertion:\n");
				getc(stdin);//Get first 'new line' from the buffer
				scanf("%[^\n]",insert);
				p=realloc(insert,(findLeght(insert)+1)*sizeof(char));
				if (!p)
				{
					printf("Error:Allocation failed!\n");
				}
				else
				{
					insert=p;
				}
				//End of input for string
				getc(stdin);//Clean the buffer
				printf("Enter the BEGIN INDEX number where the new string begins:\n");
				getc(stdin);//Clean the buffer
				scanf("%d",&begin_index);
				if(insert_string(&ccs,insert,begin_index)<0)
					printf("An error happened!\n");
			}
			else
			{
				printf("Error:CCS must be entered to perform this action!\n");

			}
			break;
		case 5://replace something from ccs
			if (*ccs)//detect if ccs entered or not
			{
				char *find,*replace;
				int replacementCount;
				//Get string to find
				p=(char*)malloc(sizeof(char)*80);
				if (!p)
				{
					printf("Error:Not enough space on memory!\n");
					return -1;
				}
				else
				{
					find=p;
				}
				printf("Find what:\n");
				getc(stdin);//Get first 'new line' from the buffer
				scanf("%[^\n]",find);
				p=(char*)realloc(find,(findLeght(find)+1)*sizeof(char));
				if (!p)
					printf("Error:Allocation failed!\n");
				else
					find=p;
				//End of getting find string
				//Get string to replace
				p=0;//mallock returns the same adress which is another variable if p has an adress
				p=(char*)malloc(sizeof(char)*80);
				if (!p)
				{
					printf("Error:Not enough space on memory!\n");
					return -1;
				}
				else
					replace=p;
				printf("Replace with what:\n");
				getc(stdin);//Get first 'new line' from the buffer
				scanf("%[^\n]",replace);
				p=(char*)realloc(replace,(findLeght(replace)+1)*sizeof(char));
				if (!p)
					printf("Error:Allocation failed!\n");
				else
					replace=p;
				//End of getting replace string
				getc(stdin);//clear buffer
				replacementCount=replace_string(&ccs,find,replace);
				if(replacementCount<0)
					printf("An error happened!\n");
				else
					printf("%d\n",replacementCount);
			}
			else
			{
				printf("Error:CCS must be entered to perform this action!\n");
			}
			break;
		default:
			printf("Seems like there is a non valid input, try again maybe? \n");
		}
		printf("CCS:%s\n",ccs);
	}
	return 0;
}

int user_menu (){
	int choosen;
	printf("0: Exit the program\n1: Set Current Character Sequence\n2: Get Substring\n3: Remove Substring\n4: Insert\n5: Replace\n");
	printf("Your choise:\n");
	scanf("%d",&choosen);
	return choosen;
}

int set_ccs(char **ccs)
{
	int i=0;
	char *p;
	free(*ccs);//Free the storage of old CCS
	printf("Enter CCS:");
	p=(char*)malloc(80*sizeof(char));
	if (!p)
	{
		printf("Allocation failed!\n");
		return -1;
	}
	else
	{
		*ccs=p;
	}
	getc(stdin);//Get first 'new line' from the buffer
	scanf("%[^\n]",(*ccs));
	p=realloc((*ccs),findLeght(*ccs)*sizeof(char));
	if (!p)
	{
		printf("Reallocation failed!\n");
		return -1;
	}
	else
	{
		*ccs=p;
	}
	return findLeght(*ccs)*sizeof(char);
}

char *sub_string (char *ccs, int begin_index, int end_index)
{
	int lenght,size;
	char *p,*tmp;
	lenght=findLeght(ccs);
	if (begin_index<0 || end_index>lenght || end_index<0 || end_index<begin_index) //check if inputs are valid
	{
		return NULL;
	}
	else
	{
		size=end_index-begin_index+1;
		p=malloc((size+1)*sizeof(char));
		if(p)
		{
			memcpy(p,ccs+begin_index*sizeof(char),size);
			tmp=p+size*sizeof(char);
			*tmp='\0';//add null to end of the string
		}
		else
		{
			printf("Allocation failed!\n");
			return NULL;
		}
	}
	return p;
}

char *remove_string(char **ccs, int begin_index, int end_index)
{
	int lenght=0,size,tmp;
	char * p1,*p2,*substr,*lastCharacter;
	lenght=findLeght(*ccs);
	if (begin_index<0 || end_index>lenght || end_index<0 || end_index<begin_index)//check if inputs are valid
		return NULL;
	else
	{
		size=end_index-begin_index+1;
		p1=(*ccs)+begin_index*sizeof(char); //starting point to remove
		p2=p1+sizeof(char)*size; //ending point to remove
		substr=malloc((size+1)*sizeof(char));
		if(substr)
		{
			memcpy(substr,p1,size); //get substr
			lastCharacter=substr+((size+1)*sizeof(char));
			*lastCharacter='\0'; //add null to end of the string
		}
		else
		{
			printf("Allocation failed!\n");
			return NULL;
		}
		memcpy(p1,p2,(lenght-end_index+1)); //delete the necessary part
		p1=realloc(*ccs,(lenght-size+1)*sizeof(char));
		if(p1)
		{
			*ccs=p1;
		}
		else
		{
			printf("Allocation failed!\n");
			return NULL;
		}
	}
	return substr;
}

int insert_string(char **ccs, char *insert, int begin_index)
{
	int lenghtC=0,lenghtI=0;
	char * p1,*p2,*lastCharacter;
	lenghtC=findLeght(*ccs);
	lenghtI=findLeght(insert);
	p1=realloc((*ccs),lenghtI+lenghtC);
	if(!p1)
	{
		printf("Allocation failed!\n");
		return -1;
	}
	*ccs=p1;
	p1=p1+begin_index*sizeof(char);//carry pointer to start of the insertion
	memcpy(p1+lenghtI*sizeof(char),p1,(lenghtC-begin_index)*sizeof(char)); //slide the necessary part
	memcpy(p1,insert,lenghtI*sizeof(char));//insert string
	return (lenghtI+lenghtC)*sizeof(char);
}

int replace_string(char **ccs, char *find, char *replace)
{
	int lenghtC,lenghtR,lenghtF,found=0;
	char *p1,*p2,*p3;
	printf("find:%s replace:%s\n",find,replace);
	lenghtC=findLeght(*ccs);
	lenghtR=findLeght(replace);
	lenghtF=findLeght(find);
	p1=*ccs;
	printf("CCS before change:%s\n",p1);
	while(*p1)//scan ccs char by char
	{
		p2=find;
		p3=p1;
		while(*p1==*p2 && *p2!='\0')//scan ccs and find char by char to find a match
		{
			p1+=sizeof(char);
			p2+=sizeof(char);
		}
		if(*p2=='\0') //found a match
		{
			p2=realloc(*ccs,lenghtC-lenghtF+lenghtR);//we are done with p2 so we can reuse it again
			if(p2)
			{
				p1=(p1-*ccs)+p2;
				p3=(p3-*ccs)+p2;
				//adapt other adresses used to realloc
				*ccs=p2;
			}
			else
			{
				printf("Allocation failed!\n");
				return -1;
			}
			memcpy(p1+(lenghtR-lenghtF)*sizeof(char),p1,(lenghtC+1)*sizeof(char)-(p1-*ccs));//slide the necessarry part
			memcpy(p3,replace,lenghtR*sizeof(char));//overwrite and change necessary part
			found++;
			lenghtC=findLeght(*ccs);
		}
		p1+=sizeof(char);
	}
	return found;
}

int findLeght(char* str)//get a length of a string
{
	int lenght=0;
	while (*str)
	{
		lenght++;
		str+=sizeof(char);
	}
	return lenght;
}