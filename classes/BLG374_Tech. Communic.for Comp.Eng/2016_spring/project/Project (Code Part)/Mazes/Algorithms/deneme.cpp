#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <stdio.h>   // for getchar()
#include <fstream>   // for file operations
//#include <string>    // for string methods
#include <cstdlib>   // standard library
#include <ctime>     // for time measurements
#include <unistd.h>
#include <math.h>
#include <queue>
#include <stack>

void DFS(int x,int y,char maze[51][101]);
void BFS(int x,int y,char maze[51][101]);
void Astar(int x,int y,char Maze[51][101]);
void printMaze(char maze[51][101]);
void Djikstra(int x,int y,char Maze[51][101]);
int heuristic(int x,int y);

int end_maze[10][10][2];
int indicator;

int main(int argv, char **argc){
  std::ifstream read;//reading from file
  char maze[10][51][101]; //first indicates maze number (there are 10 in this case), and every maze is 50x50
  char tmpMaze[51][101];
  int start_maze[10][2];
  
  for(int i = 0;i<10;i++)
    for(int j = 0;j<10;j++)
      for(int k = 0;k<2;k++)
        end_maze[i][j][k]=-1;

  char a,tmp;
  for(int i = 1 ;i <= 10;i++){
    if(argc[i] == NULL){
      std::cout << "The next file is not included please try again. Expected 10 have " << i - 1 << "." << std::endl;
      std::cout << "Exiting now..." << std::endl;
      exit(1);
    }

    read.open(argc[i]); //openning files with order
    int x = 0, y = 0;
    int endC=0;
    if(read.is_open()){
      std::cout << "Reading file " << argc[i] << "." << std::endl;
      read.get(a); //getting the trash characters
      read.get(a); //getting the trash characters
      //reading until the end of file
      while(read.get(a)){
        if(y < 101){
          if(a == 'S'){
            start_maze[i - 1][0] = x;
            start_maze[i - 1][1] = y;
          }
          if(a == 'E'){
            end_maze[i-1][endC][0]=x;
            end_maze[i-1][endC][1]=y;
            endC++;
          }
          maze[i - 1][x][y] = a;
        }
        y++;
        //if next line then y = 0
        if(a == '\n'){
          x++;
          y = 0;
        }
      }
      std::cout << "File " << argc[i] << " has been read sucessfully!" << std::endl << std::endl;
      read.close(); //closing openned file

      std::cout << "Test" << i << ". Printing file " << argc[i] << std::endl << std::endl;
      std::cout << "Starting point for maze " << argc[i] << " is (" << start_maze[i - 1][0] << ", " << start_maze[i - 1][1] << ")." << std::endl;
      for(int ix = 0;ix < 52;ix++){
        for(int ye  = 0;ye < 101;ye++){
          std::cout<< maze[i - 1][ix][ye];
          tmpMaze[ix][ye]=maze[i - 1][ix][ye];
        }
        std::cout << std::endl;
      }
      std::cout << "Please hit enter to continue..." << std::endl;
      getchar();
    }
    else{
      std::cout << "Could not open the file with name: " << argc[i] << std::endl;
    }

    indicator=i;

    
    system("clear");

    std::cout<<"DFS:"<<std::endl;
    DFS(start_maze[i-1][0],start_maze[i-1][1],tmpMaze);
    printMaze(tmpMaze);

    for(int ix = 0;ix < 52;ix++){
      for(int ye  = 0;ye < 101;ye++){
        tmpMaze[ix][ye]=maze[i - 1][ix][ye];
      }
    }

    getchar();
    system("clear");

    std::cout<<"DFS:"<<std::endl;
    BFS(start_maze[i-1][0],start_maze[i-1][1],tmpMaze);
    printMaze(tmpMaze);

    for(int ix = 0;ix < 52;ix++){
      for(int ye  = 0;ye < 101;ye++){
        tmpMaze[ix][ye]=maze[i - 1][ix][ye];
      }
    }

    getchar();

    system("clear");
    Astar(start_maze[i-1][0],start_maze[i-1][1],tmpMaze);
    printMaze(tmpMaze);

    for(int ix = 0;ix < 52;ix++){
      for(int ye  = 0;ye < 101;ye++){
        tmpMaze[ix][ye]=maze[i - 1][ix][ye];
      }
    }

    getchar();
    
    system("clear");
    Djikstra(start_maze[i-1][0],start_maze[i-1][1],tmpMaze);
    printMaze(tmpMaze);

    getchar();

  }//end of main for

  return 0;
}

#define multiplerY 2
#define multiplerX 1

void DFS(int x,int y,char Maze[51][101]){
    using namespace std;
    stack<int> xStack;
    stack<int> yStack;
    int numberOfDirections;
    int U,L,D,R;
    while(Maze[x][y]!='E' && Maze[x][y-multiplerY]!='E' && Maze[x][y+multiplerY]!='E' && Maze[x-multiplerX][y]!='E' && Maze[x+multiplerX][y]!='E'){
        numberOfDirections=0;
        U=0;L=0;D=0;R=0;
        if(Maze[x][y-multiplerY]==' '){
            U=1;
            //Up
            numberOfDirections++;
        }
        if(Maze[x-multiplerX][y]==' '){
            L=1;
            //Left
            numberOfDirections++;
        }
        if(Maze[x][y+multiplerY]==' '){
             D=1;
            //Down
            numberOfDirections++;
        }
        if(Maze[x+multiplerX][y]==' '){
            R=1;
            //Right
            numberOfDirections++;
        }
        if(numberOfDirections==0){
            x=xStack.top();
            xStack.pop();
            y=yStack.top();
            yStack.pop();
        }
        else if(numberOfDirections==1){
            x=x+(R-L)*multiplerX;
            y=y+(D-U)*multiplerY;
            Maze[x][y]='o';
        }
        else if(numberOfDirections>1){
            xStack.push(x);
            yStack.push(y);
            if(U)
                y-=multiplerY;
            else if(R)
                x+=multiplerX;
            else if(D)
                y+=multiplerY;
            else if(L)
                x-=multiplerX;
            Maze[x][y]='o';
        }
    }
}


void BFS(int x,int y,char Maze[51][101]){
    using namespace std;
    queue<int> xQue;
    queue<int> yQue;
    int U,L,D,R;
    int numberOfDirections;
    while(Maze[x][y]!='E' && Maze[x][y-1]!='E' && Maze[x][y+1]!='E' && Maze[x-1][y]!='E' && Maze[x+1][y]!='E'){
        numberOfDirections=0;
        U=0;L=0;D=0;R=0;
        if(Maze[x][y-multiplerY]==' '){
            U=1;
            //Up
            numberOfDirections++;
        }
        if(Maze[x-multiplerX][y]==' '){
            L=1;
            //Left
            numberOfDirections++;
        }
        if(Maze[x][y+multiplerY]==' '){
             D=1;
            //Down
            numberOfDirections++;
        }
        if(Maze[x+multiplerX][y]==' '){
            R=1;
            //Right
            numberOfDirections++;
        }
        if(numberOfDirections==0){
            printMaze(Maze);
            x=xQue.front();
            xQue.pop();
            y=yQue.front();
            yQue.pop();
        }
        else if(numberOfDirections==1){
            x=x+(R-L)*multiplerX;
            y=y+(D-U)*multiplerY;
            Maze[x][y]='o';
        }
        else if(numberOfDirections>1){
            //add to decision queue
            cout<<"Created new decision queue: "<<x<<"-"<<y<<endl;
            //Push
            xQue.push(x);
            yQue.push(y);
            if(U)
                y-=multiplerY;
            else if(R)
                x+=multiplerX;
            else if(D)
                y+=multiplerY;
            else if(L)
                x-=multiplerX;
            Maze[x][y]='o';
        }
        
    }
}

struct node
  {
    int gScore;
    int hScore;
    int fScore;
    int x;
    int y;
  };

class comp {
public:
    bool operator() (node n1, node n2) const {
        //std::cout<<"n1:"<<n1.gScore<<"-"<<n1.hScore<<"-"<<n1.fScore<<" n2:"<<n2.gScore<<"-"<<n2.hScore<<"-"<<n2.fScore<<std::endl;
        return n1.fScore>n2.fScore;
    }
};

void Astar(int x,int y,char Maze[51][101]){
  printMaze(Maze);
  getchar();
  std::priority_queue<node,std::vector<node>,comp> open;
  node tmp;
  tmp.gScore=0;
  tmp.hScore=0;
  tmp.fScore=0;
  tmp.x=x;
  tmp.y=y;
  open.push(tmp);
  Maze[tmp.x][tmp.y]='o';

  int cost=0;
  int g[51][101];
  for(int i=0;i<51;i++)
    for(int j=0;j<101;j++)
      g[i][j]=-1;

  while(!open.empty() && Maze[tmp.x][tmp.y]!='E'){
    
    tmp=open.top();
    open.pop();
    Maze[tmp.x][tmp.y]='c';
    
    //Komşular:
    cost=tmp.gScore+1;

    //R:
    if(Maze[tmp.x+multiplerX][tmp.y]!='E'){
      if(Maze[tmp.x+multiplerX][tmp.y]=='o' && cost<g[tmp.x+multiplerX][tmp.y]){
        Maze[tmp.x+multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x+multiplerX][tmp.y]=='c' && cost<g[tmp.x+multiplerX][tmp.y]){
        Maze[tmp.x+multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x+multiplerX][tmp.y]!='o' && Maze[tmp.x+multiplerX][tmp.y]!='c' && Maze[tmp.x+multiplerX][tmp.y]!='*'){
          g[tmp.x+multiplerX][tmp.y]=cost;
          Maze[tmp.x+multiplerX][tmp.y]='o';
          tmp.gScore=cost;
          tmp.hScore=heuristic(tmp.x,tmp.y);
          tmp.fScore=cost+tmp.hScore;
          tmp.x=tmp.x+multiplerX;
          //tmp.y=tmp.y;
          open.push(tmp);
      }
    }else  tmp.x=tmp.x+multiplerX;

    //L:
    if(Maze[tmp.x-multiplerX][tmp.y]!='E'){
      if(Maze[tmp.x-multiplerX][tmp.y]=='o' && cost<g[tmp.x-multiplerX][tmp.y]){
        Maze[tmp.x-multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x-multiplerX][tmp.y]=='c' && cost<g[tmp.x-multiplerX][tmp.y]){
        Maze[tmp.x-multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x-multiplerX][tmp.y]!='o' && Maze[tmp.x-multiplerX][tmp.y]!='c'  && Maze[tmp.x-multiplerX][tmp.y]!='*'){
          g[tmp.x+multiplerX][tmp.y]=cost;
          Maze[tmp.x-multiplerX][tmp.y]='o';
          tmp.gScore=cost;
          tmp.hScore=heuristic(tmp.x,tmp.y);
          tmp.fScore=cost+tmp.hScore;
          tmp.x=tmp.x-multiplerX;
          //tmp.y=tmp.y;
          open.push(tmp);
      }
    }else tmp.x=tmp.x-multiplerX;

    //U:
    if(Maze[tmp.x][tmp.y+multiplerY]!='E'){
      if(Maze[tmp.x][tmp.y+multiplerY]=='o' && cost<g[tmp.x][tmp.y+multiplerY]){
        Maze[tmp.x][tmp.y+multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y+multiplerY]=='c' && cost<g[tmp.x][tmp.y+multiplerY]){
        Maze[tmp.x][tmp.y+multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y+multiplerY]!='o' && Maze[tmp.x][tmp.y+multiplerY]!='c' && Maze[tmp.x][tmp.y+multiplerY]!='*'){
          g[tmp.x][tmp.y+multiplerY]=cost;
          Maze[tmp.x][tmp.y+multiplerY]='o';
          tmp.gScore=cost;
          tmp.hScore=heuristic(tmp.x,tmp.y);
          tmp.fScore=cost+tmp.hScore;
          //tmp.x=tmp.x;
          tmp.y=tmp.y+multiplerY;
          open.push(tmp);
      }
    }else tmp.y=tmp.y+multiplerY;

    //D:
    if(Maze[tmp.x][tmp.y-multiplerY]!='E'){
      if(Maze[tmp.x][tmp.y-multiplerY]=='o' && cost<g[tmp.x][tmp.y-multiplerY]){
        Maze[tmp.x][tmp.y-multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y*multiplerY]=='c' && cost<g[tmp.x][tmp.y-multiplerY]){
        Maze[tmp.x][tmp.y+multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y-multiplerY]!='o' && Maze[tmp.x][tmp.y*multiplerY]!='c' && Maze[tmp.x][tmp.y-multiplerY]!='*'){
          g[tmp.x][tmp.y-multiplerY]=cost;
          Maze[tmp.x][tmp.y-multiplerY]='o';
          tmp.gScore=cost;
          tmp.hScore=heuristic(tmp.x,tmp.y);
          tmp.fScore=cost+tmp.hScore;
          //tmp.x=tmp.x;
          tmp.y=tmp.y-multiplerY;
          open.push(tmp);
      }
    }else tmp.y=tmp.y-multiplerY;
  }
  //Euclidean distance
  /*
  function heuristic(node) =
    dx = abs(node.x - goal.x)
    dy = abs(node.y - goal.y)
    return D * sqrt(dx * dx + dy * dy)
  */
  //Take minumum for each exit

}

void Djikstra(int x,int y,char Maze[51][101]){
  printMaze(Maze);
  getchar();
  std::priority_queue<node,std::vector<node>,comp> open;
  node tmp;
  tmp.gScore=0;
  tmp.hScore=0;
  tmp.fScore=0;
  tmp.x=x;
  tmp.y=y;
  open.push(tmp);
  Maze[tmp.x][tmp.y]='o';

  int cost=0;
  int g[51][101];
  for(int i=0;i<51;i++)
    for(int j=0;j<101;j++)
      g[i][j]=-1;

  while(!open.empty() && Maze[tmp.x][tmp.y]!='E'){
    
    tmp=open.top();
    open.pop();
    Maze[tmp.x][tmp.y]='c';
    
    //Komşular:
    cost=tmp.gScore+1;

    //R:
    if(Maze[tmp.x+multiplerX][tmp.y]!='E'){
      if(Maze[tmp.x+multiplerX][tmp.y]=='o' && cost<g[tmp.x+multiplerX][tmp.y]){
        Maze[tmp.x+multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x+multiplerX][tmp.y]=='c' && cost<g[tmp.x+multiplerX][tmp.y]){
        Maze[tmp.x+multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x+multiplerX][tmp.y]!='o' && Maze[tmp.x+multiplerX][tmp.y]!='c' && Maze[tmp.x+multiplerX][tmp.y]!='*'){
          g[tmp.x+multiplerX][tmp.y]=cost;
          Maze[tmp.x+multiplerX][tmp.y]='o';
          tmp.gScore=cost;
          tmp.hScore=0;
          tmp.fScore=cost+tmp.hScore;
          tmp.x=tmp.x+multiplerX;
          //tmp.y=tmp.y;
          open.push(tmp);
      }
    }else  tmp.x=tmp.x+multiplerX;

    //L:
    if(Maze[tmp.x-multiplerX][tmp.y]!='E'){
      if(Maze[tmp.x-multiplerX][tmp.y]=='o' && cost<g[tmp.x-multiplerX][tmp.y]){
        Maze[tmp.x-multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x-multiplerX][tmp.y]=='c' && cost<g[tmp.x-multiplerX][tmp.y]){
        Maze[tmp.x-multiplerX][tmp.y]=' ';
      }
      if(Maze[tmp.x-multiplerX][tmp.y]!='o' && Maze[tmp.x-multiplerX][tmp.y]!='c'  && Maze[tmp.x-multiplerX][tmp.y]!='*'){
          g[tmp.x+multiplerX][tmp.y]=cost;
          Maze[tmp.x-multiplerX][tmp.y]='o';
          tmp.gScore=cost;
          tmp.hScore=0;
          tmp.fScore=cost+tmp.hScore;
          tmp.x=tmp.x-multiplerX;
          //tmp.y=tmp.y;
          open.push(tmp);
      }
    }else tmp.x=tmp.x-multiplerX;

    //U:
    if(Maze[tmp.x][tmp.y+multiplerY]!='E'){
      if(Maze[tmp.x][tmp.y+multiplerY]=='o' && cost<g[tmp.x][tmp.y+multiplerY]){
        Maze[tmp.x][tmp.y+multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y+multiplerY]=='c' && cost<g[tmp.x][tmp.y+multiplerY]){
        Maze[tmp.x][tmp.y+multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y+multiplerY]!='o' && Maze[tmp.x][tmp.y+multiplerY]!='c' && Maze[tmp.x][tmp.y+multiplerY]!='*'){
          g[tmp.x][tmp.y+multiplerY]=cost;
          Maze[tmp.x][tmp.y+multiplerY]='o';
          tmp.gScore=cost;
          tmp.hScore=0;
          tmp.fScore=cost+tmp.hScore;
          //tmp.x=tmp.x;
          tmp.y=tmp.y+multiplerY;
          open.push(tmp);
      }
    }else tmp.y=tmp.y+multiplerY;

    //D:
    if(Maze[tmp.x][tmp.y-multiplerY]!='E'){
      if(Maze[tmp.x][tmp.y-multiplerY]=='o' && cost<g[tmp.x][tmp.y-multiplerY]){
        Maze[tmp.x][tmp.y-multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y*multiplerY]=='c' && cost<g[tmp.x][tmp.y-multiplerY]){
        Maze[tmp.x][tmp.y+multiplerY]=' ';
      }
      if(Maze[tmp.x][tmp.y-multiplerY]!='o' && Maze[tmp.x][tmp.y*multiplerY]!='c' && Maze[tmp.x][tmp.y-multiplerY]!='*'){
          g[tmp.x][tmp.y-multiplerY]=cost;
          Maze[tmp.x][tmp.y-multiplerY]='o';
          tmp.gScore=cost;
          tmp.hScore=0;
          tmp.fScore=cost+tmp.hScore;
          //tmp.x=tmp.x;
          tmp.y=tmp.y-multiplerY;
          open.push(tmp);
      }
    }else tmp.y=tmp.y-multiplerY;
  }
}

int heuristic(int x,int y){
  int i,j=9999;
  for(int k=0;k<10;k++){
    i=sqrt(pow(x-end_maze[indicator][k][0],2)+pow(y-end_maze[indicator][k][1],2));
    if(i<j)j=i;
  }
  return j;
}

void printMaze(char maze[51][101]){
    sleep(0.1);
    //getchar();
    system("clear");
    for(int ix = 0;ix < 52;ix++){
      for(int ye  = 0;ye < 101;ye++){
        std::cout<< maze[ix][ye];
      }
      std::cout << std::endl;
    }

}
