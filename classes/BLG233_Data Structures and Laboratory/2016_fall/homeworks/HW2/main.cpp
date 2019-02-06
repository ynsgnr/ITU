#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 31.10.2016
*/

//TODO add search and match in get database

//Implementations:

#define SNAME_LENGTH 50
#define LNAME_LENGTH 50
#define STYLE_LENGTH 30
#define SINGER_LENGTH 50

#define FILENAME "songbook.txt"

typedef struct song song;
typedef struct song_node song_node;
typedef struct playlist playlist;

struct song {
  char* name   = new char[SNAME_LENGTH];
  char* singer = new char[SINGER_LENGTH];
  char* style  = new char[STYLE_LENGTH];
  int year;
};

struct song_node {
  song* data;
  song_node* next;
  song_node* prev;
  playlist* parent;
};

struct playlist {
  int songnumber;
  char* name = new char[LNAME_LENGTH];
  song_node* head;
  playlist* next;
  playlist* prev;
};

struct list {
  int playlist_count;
  playlist* head;
};

playlist* createList(char *,int); //Create new list by 1.style 2.singer 3.from playlists 4.from songs and 0.an empty list
void addSong(song*, playlist*); //Add songs to custom playlist from sorted playlist
void play();//1.Play list 2.play list by a song in it 3. play a single song
void removeSong(song_node *); //remove choosen song from custom playlist
void deleteList(playlist *); //delete list
void printList(); // Navigate in lists with commands like Next,Previous, Select, Exit
void writeToFile(); //Write all playlists to "songbook.txt" (1st Chronological) separate playlists by "*****"
void exit();//Save and close

//--End of Implementations--

song_node* songs(playlist *); //Print all songs from a list, return choosen song
playlist* lists(); //Print all lists, return choosen list
bool menu(); //Prints menu and calls the function related to user's input
void getDatabase(); //Install db from file
void createSong(song); //Add song to sorted,Chronological and random list separately
song getSong(char*); //Gets song from line in the file
song* findSong(song); //Find song's data pointer from the sorted list
void randomize(); //Randomize the random list
bool compare(song*,song*); //Check if song data equal or not


list playlists;

int main()
{
    bool dontClose = true;
    cout << "Loading..." << endl;
    //initialize
    playlist* chronList=new playlist;
    playlist* sortList=new playlist;
    playlist* randList=new playlist;
    playlists.playlist_count=3;
    playlists.head=chronList;
    chronList->name="Chronological List";
    chronList->head=NULL;
    chronList->next=sortList;
    chronList->prev=randList;
    chronList->songnumber=0;
    sortList->name="Sorted List";
    sortList->head=NULL;
    sortList->next=randList;
    sortList->prev=chronList;
    sortList->songnumber=0;
    randList->name="Random List";
    randList->head=NULL;
    randList->next=chronList;
    randList->prev=sortList;
    randList->songnumber=0;

    //start the program
    getDatabase();
    //Menu Loop
    while (dontClose){
        dontClose=menu();
    }
    return 0;
}

void getDatabase()
{
    string line;
    playlist* pl;
    song s;
    ifstream songbook (FILENAME);
      if (songbook.is_open())
      {
            getline(songbook,line);
            while (strcmp(line.c_str(),"*****") && songbook.good()){
                //get all songs
                createSong(getSong(const_cast<char*>(line.c_str())));
                getline(songbook,line);
            }
            getline(songbook,line);
            while(songbook.good()){
                pl=createList((const_cast<char*>(line.c_str())),0);
                getline(songbook,line);
                while(strcmp(line.c_str(),"*****") && songbook.good()){
                    s=getSong(const_cast<char*>(line.c_str()));
                    addSong(findSong(s),pl);
                    getline(songbook,line);
                    }
                getline(songbook,line);
                }
            songbook.close();
      }
      else cout << "Unable to open file";

}

song getSong(char* c){
        song tmp;
        int j=0;
        while(*c!='\t'){
            tmp.name[j]=c[0];
            j++;
            c++;
        }
        tmp.name[j]='\0';
        j=0;
        c++;
        while(*c!='\t'){
            tmp.singer[j]=c[0];
            j++;
            c++;
        }
        tmp.singer[j]='\0';
        j=0;
        c++;
        while(*c!='\t'){
            tmp.style[j]=c[0];
            j++;
            c++;
        }
        tmp.style[j]='\0';
        tmp.year=atoi(tmp.style);//used tmp.style for memory optimization
        j=0;
        c++;
        while(*c!='\0'){
            tmp.style[j]=c[0];
            j++;
            c++;
        }
        if(tmp.style[j-1]=='\r')tmp.style[j-1]='\0';
        else tmp.style[j]='\0';
        return tmp;
}

song* findSong(song s){
    playlist* pl = playlists.head->next; //Sorted list
    song* found=NULL;
    song_node* node=pl->head;
    int i=0;
    int songNum = pl->songnumber;
    while(i<songNum && compare(found,&s)){
        found=node->data;
        node=node->next;
        i++;
    }
    if (i>songNum){
        cout<<"Corrupted file,ignoring non-existing song"<<endl; //No match found
        found=NULL;
    }
    return found;
}

bool compare(song* s1, song* s2){
    //Return false if song data is same
    //Return true if song data is different
    if (s1==NULL || s2==NULL)
        return true; //invalid compare
    else if (!strcmp(s1->name,s2->name) && !strcmp(s1->singer,s2->singer) && !strcmp(s1->style,s2->style) && s1->year==s2->year)
        return false; //same song
}

void createSong(song s){
    int year=0,songCounter=0;

    playlist* chronList=playlists.head;
    playlist* sortList=chronList->next;
    playlist* randList=sortList->next;

    //Chronological List
    song* tmp=new song;
    (*tmp)=s;
    song_node *node=new song_node;
    node->data=tmp;
    node->parent=chronList;
    song_node *checkThis=chronList->head;
    if(checkThis==NULL){
        //Empty list create head
        chronList->head=node;
        node->next=node;
        node->prev=node;
    }
    else{
        while((tmp->year)>year && songCounter<(chronList->songnumber)){
            //Compare and move in the list
            year=checkThis->data->year;
            checkThis=checkThis->next;
            songCounter++;
        }
        //Insert
        node->next=checkThis;
        node->prev=checkThis->prev;
        checkThis->prev->next=node;
        checkThis->prev=node;
    }
    (chronList->songnumber)++;

    //Sorted List
    node=new song_node;
    node->data=tmp;
    node->parent=sortList;
    checkThis=sortList->head;
    if(checkThis==NULL){
        //Empty list create head
        sortList->head=node;
        node->next=node;
        node->prev=node;
    }
    else{
        songCounter=0;
        while(( strcmp(tmp->singer,checkThis->data->singer)<0)
              && songCounter<sortList->songnumber){
            //Compare and move in the list
            checkThis=checkThis->next;
            songCounter++;
        }
        while(( strcmp(tmp->name,checkThis->data->name)<0)
              && songCounter<sortList->songnumber){
            //Compare and move in the list
            checkThis=checkThis->next;
            songCounter++;
        }
        //Insert
        node->next=checkThis;
        node->prev=checkThis->prev;
        checkThis->prev->next=node;
        checkThis->prev=node;
    }
    (sortList->songnumber)++;

    //Random List
    node=new song_node;
    node->data=tmp;
    node->parent=randList;
    if(checkThis==NULL){
        //Empty list create head
        randList->head=node;
        node->next=node;
        node->prev=node;
    }
    else{
        //Insert to the end
        randList->head->prev->next=node;
        node->next=randList->head;
        node->prev=randList->head->prev;
        randList->head->prev=node;
    }
    (randList->songnumber)++;

    cout<<"Song created:"<<s.name<<"-"<<s.singer<<"-"<<s.style<<"-"<<s.year<<endl;
}

playlist* createList(char *name,int option){
    /*0=empty list
     *1=songs of a specific style
     *2=songs of a specific singer
     *3=combination of existing playlists
     *4=combination of existing songs
     */
    playlist* pl;
    playlist* tmpList;
    string tmp;
    char c;
    //Use sorted list:
    song_node * node=playlists.head->next->head;
    int songNumber=playlists.head->next->songnumber;
    int i=0;
    bool t;
    //Create empty list
    pl = new playlist;
    //Link it to the last playlist:
    tmpList=playlists.head;
    tmpList->prev->next=pl;
    pl->prev=tmpList->prev;
    //Link it to the head:
    tmpList->prev=pl;
    pl->next=tmpList;
    pl->head=NULL;
    strcpy(pl->name,name);
    pl->songnumber=0;
    switch(option){
    case 0:break;
    case 1:
        //Songs with specific style
        t=true;//Check if there is a match
        cout<<"Please enter style:"<<endl;
        getchar();
        getline(cin,tmp);
        for(i=0;i<songNumber;i++){
            if(!strcmp(node->data->style,const_cast<char*>(tmp.c_str()))){
                addSong(node->data,pl);
                t=false;
            }
            node=node->next;
        }
        if(t)cout<<"No match found"<<endl;
        break;
    case 2:
        //songs of a specific singer
        t=true;//Check if there is a match
        cout<<"Please enter singer:"<<endl;
        getchar();
        getline(cin,tmp);
        for(i=0;i<songNumber;i++){
            if(!strcmp(node->data->singer,const_cast<char*>(tmp.c_str()))){
                addSong(node->data,pl);
                t=false;
            }
            node=node->next;
        }
        if(t)cout<<"No match found"<<endl;
        break;
    case 3:
        //combination of existing playlists
        do{
            tmpList=lists();
            node=tmpList->head;
            for(i=0; i<(tmpList->songnumber) ;i++){
                addSong(node->data,pl);
                node=node->next;
            }
            cout<<"Contuine adding?(Y/N)"<<endl;
            getchar();
            c=getchar();
        }while(c!='N');
        break;
    case 4:
        do{
            node=songs(lists());
            addSong(node->data,pl);
            cout<<"Contuine adding?(Y/N)"<<endl;
            getchar();
            c=getchar();
        }while(c!='N');
        break;
    default:
        cout<<"Error"<<endl;
    }
    (playlists.playlist_count)++;
    cout<<"List created:"<<pl->name<<endl;
    return pl;
}

bool menu(){
    char choice;
    string tmp;
    int intTmp;
    song_node* s;
    playlist* pl;
    //system("CLS");
    //system("clear");
    cout << endl << endl;
    cout << "Welcome to winamp:" << endl;
    cout << "P:Play a song" << endl;
    cout << "L:Browse playlists" << endl;
    cout << "A:Add song to playlist" << endl;
    cout << "R:Remove song from playlist" << endl;
    cout << "C:Create a new playlist" << endl;
    cout << "D:Delete a custom playlist" << endl;
    cout << "w:Save" << endl;
    cout << "E:Exit" << endl;
    cout << "Choose an option" << endl;
    cout << endl;
    cout << "Enter your option {P, L, A, R, C, D, W, E} : ";
    cin >> choice;
    switch (choice) {
        case 'P': case 'p':
            play();
            break;
        case 'l': case 'L':
            printList();
            break;
        case 'a': case 'A':
            s=songs(playlists.head->next); //From sorted list
            cout<<"Choose a playlist to add "<<s->data->name<<":"<<endl;
            pl=lists();
            if(pl==playlists.head || pl==playlists.head->next || pl==playlists.head->next->next)
                cout<<"Can't add to Chronological, Sorted or Random lists"<<endl;
            else addSong(s->data,pl);
            break;
        case 'r': case 'R':
            pl=lists();
            if(pl==playlists.head || pl==playlists.head->next || pl==playlists.head->next->next)
                cout<<"Can't remove from Chronological, Sorted or Random lists"<<endl;
            else removeSong(songs(pl));
            break;
        case 'c': case 'C':
            cout<<"Please enter a name for playlist:"<<endl;
            getchar();
            getline(cin,tmp);
            cout<<"Create list from:"<<endl;
            cout<<"1) songs of a specific style"<<endl;
            cout<<"2) songs of a specific singer"<<endl;
            cout<<"3) a combination of existing playlists"<<endl;
            cout<<"4) a combination of existing songs"<<endl;
            cin>>intTmp;
            createList((const_cast<char*>(tmp.c_str())),intTmp);
            break;
        case 'd': case 'D':
            deleteList(lists());
            break;
        case 'w': case 'W':
            writeToFile();
            break;
        case 'e': case 'E':
            return 0;
            break;
        default:
            cout << "Choose a valid option:" << endl;
    }
    getchar();
    return 1;
}

void addSong(song* s, playlist* pl){
    song_node* node=new song_node;
    node->data=s;
    node->parent=pl;
    if (s!=NULL){
        if((pl->head)==NULL){
            //Empty list create head
            pl->head=node;
            node->next=node;
            node->prev=node;
        }
        else{
            node->next=pl->head;
            node->prev=pl->head->prev;
            pl->head->prev->next=node;
            pl->head->prev=node;
        }
        (pl->songnumber)++;
        cout<<"Song added:"<<s->name<<"-"<<s->singer<<"-"<<s->style<<"-"<<s->year<<" as number "<<pl->songnumber<<endl;
    }
    else cout<<"Correpted data is ignored"<<endl;
}

void play(){
    getchar(); //clean new line from stream
    char c,choice;
    string line;
    song_node* tmp;
    cout << "What would you like to play:" << endl;
    cout << "1:Play a playlist" << endl;
    cout << "2:Play a playlist starting from a specific song" << endl;
    cout << "3:Play a song" << endl;
    c=getchar();
    switch(c){
    case '1':
        tmp=lists()->head;
        do{
            cout<<"Playing:"<<tmp->data->name<<"-"<<tmp->data->singer<<"-"<<tmp->data->year<<"-"<<tmp->data->style<<endl;
            cout<<"Press for a command: N (NEXT), P (PREVIOUS) or E (EXIT)"<<endl;
            getchar(); //clean new line from stream
            choice=getchar();
            if (choice=='N') tmp=tmp->next;
            else if(choice=='P') tmp=tmp->prev;
            else cout<<"Exiting"<<endl;
        }while (choice!='E');
        break;
    case '2':
        tmp = songs(lists());
        do{
            cout<<"Playing:"<<tmp->data->name<<"-"<<tmp->data->singer<<"-"<<tmp->data->year<<"-"<<tmp->data->style<<endl;
            cout<<"Press for a command: N (NEXT), P (PREVIOUS) or E (EXIT)"<<endl;
            getchar(); //clean new line from stream
            choice=getchar();
            if (choice=='N') tmp=tmp->next;
            else if(choice=='P') tmp=tmp->prev;
        }while (choice!='E');
        break;
    case '3':
        tmp = songs(lists());
        cout<<"Playing:"<<tmp->data->name<<"-"<<tmp->data->singer<<"-"<<tmp->data->year<<"-"<<tmp->data->style<<endl;
        cout<<"Press a button to exit."<<endl;
        getchar(); //clean new line from stream
        choice=getchar();
        //TODO Remove tmp
        break;
    default:
        cout<<"Wrong Choose"<<endl;
    }
}

void removeSong(song_node *node){
    if (node->parent->head == node){
        node->parent->head=node->next;
    }
    node->prev->next=node->next;
    node->next->prev=node->prev;
    (node->parent->songnumber)--;
    delete node;
}

void deleteList(playlist* pl){
    playlist* chronList=playlists.head;
    if(pl==chronList || pl==chronList->next || pl==chronList->next->next)
        cout<<"Can't delete Chronological, Sorted or Random List"<<endl;
    else{
        song_node* node=pl->head;
        for(int i=0;i<pl->songnumber;i++){
            pl->head=node->next;
            delete node;
            node=pl->head;
        }
        pl->prev->next=pl->next;
        pl->next->prev=pl->prev;
        delete pl->name;
        delete pl;
    }
    playlists.playlist_count--;
}

void printList(){
    char choice;
    playlist* pl = playlists.head;
    playlist* tmp = pl;
    song_node* node;
    int i;
    do{
        i=1;
        cout<<"All"<<playlists.playlist_count<<"lists:"<<endl;
        while(i<=playlists.playlist_count){
            cout<<i<<". "<<(tmp->name)<<endl;
            tmp=tmp->next;
            i++;
        }
        tmp=playlists.head;
        node=pl->head;
        i=1;
        cout<<"Songs in "<<pl->name<<": "<<endl;
        while(i<=pl->songnumber){
            cout<<i<<". "<<node->data->name<<" - "<<node->data->singer<<" - "<<node->data->year<<" - "<<node->data->style<<endl;
            node=node->next;
            i++;
        }
        cout<<"Press for a command: N (NEXT), P (PREVIOUS) or E (EXIT)"<<endl;
        getchar(); //clean new line from stream
        choice=getchar();
        if (choice=='N') pl=pl->next;
        else if(choice=='P') pl=pl->prev;
        if (pl==playlist.head->next->next) //Random list
            randomize();
    }while(choice!='E');
}

void writeToFile(){
    FILE * songbook;
    song_node* node;
    song s;
    playlist* pl = playlists.head; //chronological list
    if(!(songbook = fopen( FILENAME, "w+" ))){
        cerr << "File can not be opened" << endl;
        exit(1);
    }
    rewind(songbook);
    node=pl->head;
    s=*(node->data);
    for(int i=0;i<(pl->songnumber);i++){
        fprintf(songbook,"%s\t%s\t%d\t%s\n",s.name,s.singer,s.year,s.style);
        node=node->next;
        s=*(node->data);
    }
    pl=pl->next->next->next;//Skip sorted list and random list
    for(int i=3;i<playlists.playlist_count;i++){
        fprintf(songbook,"*****\n");
        fprintf(songbook,pl->name);
        fprintf(songbook,"\n");
        node=pl->head;
        s=*(node->data);
        for(int i=0;i<pl->songnumber;i++){
            fprintf(songbook,"%s\t%s\t%d\t%s\n",s.name,s.singer,s.year,s.style);
            node=node->next;
            s=*(node->data);
        }
        pl=pl->next;
    }

    fclose(songbook);
    cout<<"Written to the file"<<endl;
}

void exit(){
    playlist * pl;
    writeToFile();
    pl=playlists.head;
    //Delete chronological list with all the song data
    song_node* node=pl->head;
    for(int i=0;i<pl->songnumber;i++){
        pl->head=node->next;
        //Delete all songs:
        delete node->data->name;
        delete node->data->singer;
        delete node->data->style;
        delete node->data;
        delete node;
        node=pl->head;
    }
    playlists.head=pl->next;
    delete pl->name;
    delete pl;
    pl=playlists.head;
    //Delete sorted list
    node = pl->head;
    for(int i=0;i<pl->songnumber;i++){
        pl->head=node->next;
        delete node;
        node = pl->head;
    }
    playlists.head=pl->next;
    delete pl->name;
    delete pl;
    pl=playlists.head;
    //Delete random list
    node = pl->head;
    for(int i=0;i<pl->songnumber;i++){
        pl->head=node->next;
        delete node;
        node = pl->head;
    }
    playlists.head=pl->next;
    delete pl->name;
    delete pl;
    //Delete user defined lists
    for(int i=3;i<=playlists.playlist_count;i++){
        playlists.head=pl->next;
        deleteList(pl);
        pl=playlists.head;
    }
}

song_node* songs(playlist* pl){
    song_node* sngs[pl->songnumber];
    song_node* node=pl->head;
    int i=1;
    cout<<"Choose a song:"<<endl;
    while(i<=pl->songnumber){
        cout<<i<<". "<<node->data->name<<endl;
        sngs[i-1]=node;
        node=node->next;
        i++;
    }
    cin>>i;
    return sngs[i-1];
}

playlist* lists(){
    playlist* pls[playlists.playlist_count];
    playlist* pl = playlists.head;
    int i=0;
    cout<<"Choose a list:"<<endl;
    while(i<playlists.playlist_count){
        cout<<i+1<<". "<<pl->name<<endl;
        pls[i]=pl;
        pl=pl->next;
        i++;
    }
    cin>>i;
    if(i==3) randomize(); //3rd list is the random list
    return pls[i-1];
}

void randomize(){
    song_node *node=playlists.head ->next   ->next   ->head;
    //               Chronological ->Sorted ->Random ->Head of random

    song* tmp;
    int songCounter=playlists.head->next->next->songnumber;
    int randomNumber;

    srand( time( NULL ) ); // initializes the pseudo-random number generator

    randomNumber=rand() % songCounter;
    for(int i=0;i<randomNumber;i++) //Start from node and move a random amount
        node=node->next;
    playlists.head->next->next->head=node;
    node=node->next;
    song_node *randomized=node; //Every node before this one is randomized already
    songCounter--;

    for(int i=0;i<songCounter;i++){
        randomNumber=rand() % (songCounter-i);
        for(int j=0;j<randomNumber;j++) //Start from node and move a random amount
            node=node->next;
        //Switch randomized and node
        tmp=randomized->data;
        randomized->data=node->data;
        node->data=tmp;
        //Switch randomized array
        randomized=randomized->next;
        node=randomized;
    }
}

int atoi(char* s)
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
