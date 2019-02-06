#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
/*
#include <iomanip>
#include <ctype.h>*/

#define FILENAME "database.txt"
#define SEPARATOR "\t"
#define MAXREC 100

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 18.10.2016
* Variables used:
 * patrec:Patient Record structure
 * patID: Patient ID
 * tmp:Temproray
 * dontClose: determines to exit from program
 * patCount: show the number of patients in array
*/

using namespace std;

struct patient_record {
    char name[40], doctorName[40], diagnosis[40];
    int patientNumber, polyclinicNumber;
    char branchName[30];
};

typedef patient_record patrec;
patrec patients[MAXREC];

bool menu(); //Prints menu and calls the function related to user's input
void getDatabase(); //Install db from file
void printAll();    //Print all patinets in array
void searchPat(string);   //Searchs patients by branchName and prints foundings
//Override searchPat
void searchPat(int);   //Searchs patients by polyclinicNumber and prints foundings
int checkPat(patrec);  //checks if there is enough space in polyclinic. Returns 1 if there is 0 if not and -1 if new clinic needed
void addPat(patrec);    //Adds patients to array
bool newClinic(int,char*); //Creates new clinic returns 1 if succesfull 0 if not
void delPat(int);      //Deletes patients from array
void uploadDatabase();  //Writes array to file
int atoi(string); //String to int
patrec getRecord (char*); //convert lines into elements


int patCount;
FILE* patFile;

int main(){
    bool dontClose = true;

    cout << "Loading..." << endl;
    getDatabase();

    while (dontClose){
        dontClose=menu();
    }

    return 1;
}
void getDatabase () {
    patrec tmp;
    char c;
    int j;
    char temp[50];
    patFile = fopen( FILENAME, "r+" );
    if(!patFile){
        if(!(patFile = fopen( FILENAME, "w+" ))){
            cerr << "File can not be opened" << endl;
            exit(1);
        }
    }
    rewind(patFile);
    patCount=0;
    c=getc(patFile);
    /*Get data between taps*/
    while (c!=EOF)
        {
        tmp = getRecord(&c);
        addPat(tmp);
        //patients[patCount]=tmp;
    }
    fclose(patFile);
}

patrec getRecord (char *c) {
        patrec tmp;
        tmp.name[0]='\0';
        tmp.doctorName[0]='\0';
        tmp.diagnosis[0]='\0';
        tmp.branchName[0]='\0';
        int j=0;

        char temp[10];
        while(*c!='\t'){
            tmp.name[j]=*c;
            j++;
            *c=getc(patFile);
        }
        //cout << tmp.name << "-";
        tmp.name[j]='\0';
        *c=getc(patFile);
        j=0;
        while(*c!='\t'){
            tmp.doctorName[j]=*c;
            j++;
            *c=getc(patFile);
        }
        //cout << tmp.doctorName << "-";
        tmp.doctorName[j]='\0';
        *c=getc(patFile);
        j=0;
        while(*c!='\t'){
            tmp.diagnosis[j]=*c;
            j++;
            *c=getc(patFile);
        }
        //cout << tmp.diagnosis << "-";
        tmp.diagnosis[j]='\0';
        *c=getc(patFile);
        j=0;
        temp[0]='\0';
        while(*c!='\t'){
            temp[j]=*c;
            j++;
            *c=getc(patFile);
        }
        temp[j]='\0';
        tmp.patientNumber=atoi(temp);
        //cout << tmp.patientNumber << "-";
        *c=getc(patFile);
        j=0;
        temp[0]='\0';
        while(*c!='\t'){
            temp[j]=*c;
            j++;
            *c=getc(patFile);
        }
        temp[j]='\0';
        tmp.polyclinicNumber=atoi(temp);
        //cout << tmp.polyclinicNumber << "-";
        *c=getc(patFile);
        j=0;
        while(*c!='\n'){
            tmp.branchName[j]=*c;
            j++;
            *c=getc(patFile);
        }
        tmp.branchName[j]='\0';
        //cout << tmp.branchName[j-1] << endl;
        *c=getc(patFile);
        return tmp;
}

bool menu(){
    char choice;
    string tmp;
    int tmpint;
    int patID;
    patrec temp;
    system("CLS");
    //system("clear");
    cout << endl << endl;
    cout << "Hospital automation:" << endl;
    cout << "P:Prints all the patient records" << endl;
    cout << "B:Search patient by branch" << endl;
    cout << "C:Search patient by polyclinic" << endl;
    cout << "I:Insert patient record" << endl;
    cout << "R:Remove patient record" << endl;
    cout << "E:Exit" << endl;
    cout << "Choose an option" << endl;
    cout << endl;
    cout << "Enter your option {P, B, C, I, R, E} : ";
    cin >> choice;
    switch (choice) {
        case 'P': case 'p':
            printAll();
            getchar();
            break;
        case 'B': case 'b':
            cout << "Enter branch name:" << endl;
            cin >> tmp;
            searchPat(tmp);
            break;
        case 'C': case 'c':
            cout << "Enter polyclinic number:" << endl;
            cin >> tmpint;
            searchPat(tmpint);
            break;
        case 'I': case 'i': case 'ı':
            getchar();//clear new line character in the stream
            cout << "Enter name:" << endl;
            cin.getline(temp.name,40);
            cout << "Enter doctor's name:" << endl;
            cin.getline(temp.doctorName,40);
            cout << "Enter diagnosis:" << endl;
            cin.getline(temp.diagnosis,40);
            cout << "Enter patient number:" << endl;
            cin >> temp.patientNumber;
            cout << "Enter polyclinic number:" << endl;
            cin >> temp.polyclinicNumber;
            getchar();//clear new line character in the stream
            cout << "Enter branch name:" << endl;
            cin.getline(temp.branchName,30);
            addPat(temp);
            break;
        case 'R': case 'r':
            cout << "Enter patient number:" << endl;
            cin >> patID;
            delPat (patID);
            break;
        case 'E': case 'e':
            uploadDatabase();
            return 0;
        default:
            return 0;
    }
    getchar();
}

void printAll() {
    patrec tmp;
    if(!patCount)cout<<"No records"<<endl;
    for (int i = 0; i < patCount; i++) {
        tmp = *(patients+i);
        if(tmp.name[0]=='\0')cout << "" << endl;
        else cout << tmp.name << SEPARATOR << tmp.doctorName << SEPARATOR << tmp.diagnosis << SEPARATOR << tmp.patientNumber << SEPARATOR << tmp.polyclinicNumber << SEPARATOR << tmp.branchName << endl;
    }
}

void searchPat(string toFind){//Search by branch name
    int i=0;
    int length=toFind.length();
    char findThis [length];
    for (i=0;i<length;i++){
        findThis[i]=toupper(toFind[i]);
    }
    findThis[i]='\0';
    cout << "find: "<<findThis<<endl;
    for(i=0;i<patCount;i++){
        if(!strcmp((patients+i)->branchName,findThis))
            if(patients[i].name[0]=='\0')cout << "" << endl;
            else cout << patients[i].name << SEPARATOR << patients[i].doctorName << SEPARATOR << patients[i].diagnosis << SEPARATOR << patients[i].patientNumber << SEPARATOR << patients[i].polyclinicNumber << SEPARATOR << patients[i].branchName << endl;
    }
}

void searchPat(int toFind){//Search by polyclinic number
    for(int i=0;i<patCount;i++)
        if((patients+i)->polyclinicNumber==toFind)
            if((patients+i)->name[0]=='\0')cout << "" << endl;
            else cout << (patients+i)->name << SEPARATOR << (patients+i)->doctorName << SEPARATOR << (patients+i)->diagnosis << SEPARATOR << (patients+i)->patientNumber << SEPARATOR << (patients+i)->polyclinicNumber << SEPARATOR << (patients+i)->branchName << endl;
}

int checkPat(patrec pr){
    int i=0;
    bool notFound = true; //check if the same clinic number found
    int isSafe = 0; //is it safe to add record?
    while (i<patCount){
       if((patients+i)->polyclinicNumber==pr.polyclinicNumber){
            notFound=false; //found clinic number
            if((patients+(i+9))->name[0]=='\0'){
                if(!strcmp((patients+i)->branchName,pr.branchName))
                isSafe=i+1; //10th element is blank, branch is same and there is no more polyclinic it is safe to add
                //isSafe also caries info about where the record should be added
                else cout<<"Same clinic exits in another branch"<<endl;
            }
            else cout<<"Clinic is full!"<<endl;
        }
       i=i+10;
    }
    if (notFound) isSafe=-1; //If same clinic number can not be found it is safe to add but needs new clinic
    return isSafe;
}

void addPat(patrec pr){
    int isNewClinic;
    int i=0;
    isNewClinic = checkPat(pr);
    if (isNewClinic==-1){
        //create new clinic
        if (newClinic(pr.polyclinicNumber,pr.branchName)){
                addPat(pr);
                cout << "New clinic created in: " << pr.branchName <<endl;
        }
        else
            cout << "Branch is full!" << endl;
    }
    else if (isNewClinic!=0){
        //add patient
        i=isNewClinic-1; //data about where is the clinic
        while((patients+i)->name[0]!='\0') i++;
        *(patients+i)=pr;
        cout << "Patient " << pr.name << " added!" << endl;
    }

}

bool newClinic (int clinicNum, char * branch){
    int i=0;
    int compare,j;
    //Turn branch into capital letters
    while (branch[i]){
        branch[i]=toupper(branch[i]);
        i++;
    }
    i=0;
    while(i<=patCount){
        compare=strcmp(branch,(patients+i)->branchName);
        if(compare==0){ //found same branch
            if(i<=patCount){
                i=i+10;
                if(!strcmp(branch,(patients+i)->branchName))
                    return false; //no more room in branch
                if (patCount+10>MAXREC){
                    cout << "Array overflow" << endl;
                    return false;
                }
                if(clinicNum<(patients+i)->polyclinicNumber)
                    i=i-10;
                for(j=patCount;j>=i;j--){
                    *(patients+(j+10))=*(patients+j); //shift to open up space
                }
                patCount=patCount+10;
                for(j=i;j<i+10;j++){
                    (patients+j)->name[0]='\0';
                    (patients+j)->doctorName[0]='\0';
                    (patients+j)->diagnosis[0]='\0';
                    (patients+j)->patientNumber=0;
                    (patients+j)->polyclinicNumber=clinicNum;
                    strcpy((patients+j)->branchName,branch);
                }
                return true; //Succesfully created polyclinic
            }
            else if(i<MAXREC){ //branch is at the end of the array
                patCount=patCount+10;
                for(;i<patCount;i++){
                    (patients+i)->name[0]='\0';
                    (patients+i)->doctorName[0]='\0';
                    (patients+i)->diagnosis[0]='\0';
                    (patients+i)->patientNumber=0;
                    (patients+i)->polyclinicNumber=clinicNum;
                    strcpy((patients+i)->branchName,branch);
                }
                return true;
            }
            else {
                cout << "Array Overflow" << endl;
                return false;
            }
        }
        else if (compare>0){
                //Pass this branch, its smaller
                i=i+10;
                if(i>=patCount){
                    patCount=patCount+10;
                    //End of array, add branch here
                    for(j=patCount-10;j<patCount;j++){
                        (patients+j)->name[0]='\0';
                        (patients+j)->doctorName[0]='\0';
                        (patients+j)->diagnosis[0]='\0';
                        (patients+j)->patientNumber=0;
                        (patients+j)->polyclinicNumber=clinicNum;
                        strcpy((patients+j)->branchName,branch);
                    }
                    return true;
                }
        }
        else{
            //Add branch in front of this one, its bigger
            patCount=patCount+10;
            if(patCount>MAXREC){
                cout << "Array Overflow" << endl;
                return false;
            }
            for(j=patCount-1;j>i;j--){//Slide records to open up space
                *(patients+j)=*(patients+(j-10));
            }
            i=i+10;
            for(j=i-10;j<i;j++){
                (patients+j)->name[0]='\0';
                (patients+j)->doctorName[0]='\0';
                (patients+j)->diagnosis[0]='\0';
                (patients+j)->patientNumber=0;
                (patients+j)->polyclinicNumber=clinicNum;
                strcpy((patients+j)->branchName,branch);
            }
            return true;
        }
    }
}

void delPat(int patID){
    patrec tmp;
    int i,firstElement;
    for(i=0;i<patCount;i++){
        if(patID==(patients+i)->patientNumber){
            (patients+i)->name[0]='\0';
            (patients+i)->doctorName[0]='\0';
            (patients+i)->diagnosis[0]='\0';
            (patients+i)->patientNumber=0;
            (patients+i)->polyclinicNumber=0;
            (patients+i)->branchName[0]='\0';
            while((i+1)%10!=0){ //Shift records
                tmp=*(patients+(i+1));
                *(patients+(i+1))=*(patients+i);
                *(patients+i)=tmp;
                i++;
                }
        firstElement=(i/10)*10;/*get to the first element of clinic*/
        if(patients[firstElement].name[0]=='\0'){
            //remove this polyclinic
            for(int j=firstElement;j<patCount;j++){//Slide records up
                *(patients+j)=*(patients+(j+10));
            }
            patCount=patCount-10;
        }
        }
    }

}

void uploadDatabase(){
    patrec tmp;
    if(!(patFile = fopen( FILENAME, "w+" ))){
        cerr << "File can not be opened" << endl;
        exit(1);
    }
    rewind(patFile);
    for(int i=0;i<patCount;i++)
    {
        tmp=*(patients+i);
        fprintf(patFile,"%s\t%s\t%s\t%d\t%d\t%s\n",tmp.name,tmp.doctorName,tmp.diagnosis,tmp.patientNumber,tmp.polyclinicNumber,tmp.branchName);
    }
    fclose(patFile);
}

int atoi(char* s)
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
