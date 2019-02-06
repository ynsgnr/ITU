#include <stdlib.h>
#include <stdio.h>

struct {
    int personID;
    double height;
    double weight;
    double BMI;
} typedef person;

person* readFile(char[],int);
void getPatients(person*,int,int,double,char[]);
void sort(double array[][2],int);

int main(int argc,char **argv) {
    int N,M;
    double threshold;
    person *people;
    //get arguments from command line
    sscanf(argv[1],"%d",&N);
    sscanf(argv[2],"%d",&M);
    sscanf(argv[3],"%lf",&threshold);

    //get people from file
    people=readFile("./height_weight.txt",N);
    if (people==NULL)
    {
        printf("Error\n");
        return -1;
    }

    //Write M patients from N people to output.txt by threshold 
    getPatients(people,N,M,threshold,"./output.txt");

    //End the program
    free(people);
    return 0;
}

person* readFile(char* file,int N)
{
    int personID,height,weight,i;
    char tmp;
    char *firstLine;
    person *people;

    //create people
    people=malloc(N*sizeof(person));
    if(!people)
    {
        printf("Not enough memory\n");
        return NULL;
    }

    //read file
    FILE *height_weight;
    if((height_weight = fopen(file,"r"))==NULL)
    {
        printf("Error,file could not opened!\n");
        return NULL;
    }

    //eliminate first line without using unnecessary memory
    firstLine=malloc(34*sizeof(char));
    if (!firstLine)
    {
        printf("Not enough memory\n");
        return NULL;
    }
    fgets(firstLine,34,(FILE *)height_weight);//get first line
    free(firstLine);

    //process file and save data to people
    for (i=0;i<N;i++)
    {
        tmp=fgetc(height_weight);
        personID=0;
        while('0'>=tmp && tmp>'9' && tmp!=EOF)
             tmp=fgetc(height_weight);//skip unwanted chars in file
        while('0'<=tmp && tmp<='9')//get only numbers
        {
            personID=(int)personID*10+tmp-'0';//digit process
            tmp=fgetc(height_weight);
        }
        height=0;
        tmp=fgetc(height_weight);//skip tab
        while('0'<=tmp && tmp<='9')//get only numbers
        {
            height=(int)height*10+tmp-'0';//digit process
            tmp=fgetc(height_weight);
        }
        weight=0;
        tmp=fgetc(height_weight);//skip tab
        while('0'<=tmp && tmp<='9')//get only numbers
        {
            weight=(int)weight*10+tmp-'0';//digit process
            tmp=fgetc(height_weight);
        }
        people[personID-1].personID=personID;
        people[personID-1].weight=weight;
        people[personID-1].height=height;
        people[personID-1].BMI=((double)weight/(height*height))*10000;//BMI:weight(kg)/height(m)^2
        fgetc(height_weight); //Eliminate a character which causes a zero in the end of every line
    }
    fclose(height_weight);
    return people;
}

void getPatients(person* people,int N,int M,double threshold,char *file)
{
    int i,j,personID;
    double thresDif[N][2],t,patients[M][2];
    FILE *output;

    //add the absolute of threshold-BMI to thresDif for every person
    for(i=0;i<N;i++)
    {
        thresDif[i][0]=people[i].personID;
        t=(double)threshold-people[i].BMI;
        if (t<0.0)
            t*=-1;//absolute value
        thresDif[i][1]=t; 
    }

    sort(thresDif,N);

    //add first M elements from the sorted list of BMI-threshold to patients
    for (i=0;i<M;i++)
    {
        personID=thresDif[i][0];
        patients[i][0]=personID;
        patients[i][1]=people[personID-1].BMI;
    }

    sort(patients,M);

    //write patients to output
    if((output = fopen(file,"w"))==NULL)
    {
        printf("Error,file could not opened!\n");
    }
    else
    {
        fprintf(output, "Person_id\tHeight(cm)\tWeight(kg)\tBMI\n");//first line
        for (i=0;i<M;i++)
        {
            j=(int)patients[i][0]-1;//get indicator for people
            fprintf(output, "%d\t%3.f\t%2.f\t%2.2f\n",people[j].personID,people[j].height,people[j].weight,people[j].BMI);
        }
        fclose(output);
    }
}

//sort a Nx2 matrix according to 2nd column
void sort(double array[][2],int n)//BubbleSort decreasing
{   
    int i,j;
    double tmp;
    for (i=0;i<(n-1);i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if (array[j][1]<array[j+1][1])
            {
                //swap first column
                tmp=array[j][1];
                array[j][1]=array[j+1][1];
                array[j+1][1]=tmp;
                //swap second column
                tmp=array[j][0];
                array[j][0]=array[j+1][0];
                array[j+1][0]=tmp;                
            }
        }
    }
}