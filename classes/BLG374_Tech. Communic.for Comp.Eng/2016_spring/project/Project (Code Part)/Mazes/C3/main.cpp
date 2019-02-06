#include <iostream>
#include <stdio.h>   // for getchar()
#include <fstream>   // for file operations
#include <cstdlib>   // standard library
#include <ctime>     // for time measurements
#include <unistd.h>
#include <cmath>
#include <queue>
#include <stack>
#include <utility>
#include <chrono>
//please modify these when needed!
#define WALKER 'o'
#define WALLTYPE '*'
#define START 'S'
#define EXIT 'E'
#define MAX_MAZE_X 51
#define MAX_MAZE_Y 101
#define multiplerY 2
#define multiplerX 1
using namespace std;
using namespace chrono;

struct node{
  int gScore, hScore, fScore, x, y;
};

class comp{
public:
  bool operator()(node n1, node n2)const{
      //cout<<"n1:"<<n1.gScore<<"-"<<n1.hScore<<"-"<<n1.fScore<<" n2:"<<n2.gScore<<"-"<<n2.hScore<<"-"<<n2.fScore<<endl;
      return n1.fScore > n2.fScore;
  }
};

void DFS(int, int, char maze[][MAX_MAZE_Y]);                                              //function prototype
void BFS(int, int, char maze[][MAX_MAZE_Y]);                                              //function prototype
void Astar(int, int, char Maze[][MAX_MAZE_Y], int [10][2]);                               //function prototype
void printMaze(char maze[][MAX_MAZE_Y]);                                                  //function prototype
void Djikstra(int ,int ,char Maze[][MAX_MAZE_Y]);                                         //function prototype
void start_random_traversing_in_maze(char [][MAX_MAZE_Y], int, int);                      //function prototype
void sendFreshTempMaze(char maze[][MAX_MAZE_Y], char temporaryMaze[][MAX_MAZE_Y]);        //function prototype


int main(int argv, char **argc){
  ifstream read;//reading from file
  ofstream write;//for writing to the file
  char maze[10][MAX_MAZE_X][MAX_MAZE_Y]; //first indicates maze number (there are 10 in this case), and every maze is 50x50
  char tmpMaze[MAX_MAZE_X][MAX_MAZE_Y];
  int start_maze[10][2];
  int end_maze[10][10][2];
  double microseconds_holder[10][5];

  for(int i = 0;i<10;i++){
    for(int j = 0;j<10;j++){
      for(int k = 0;k<2;k++){
        end_maze[i][j][k] = -1;
      }
    }
  }

  char a,tmp;
  for(int i = 1 ;i <= 10;i++){
    if(argc[i] == NULL){
      cout << "The next file is not included please try again. Expected 10 have " << i - 1 << "." << endl;
      cout << "Exiting now..." << endl;
      exit(1);
    }

    read.open(argc[i]); //openning files with order
    int x = 0, y = 0,endC = 0;

    if(read.is_open()){
      cout << "Reading file " << argc[i] << "." << endl;
      read.get(a); //getting the trash characters
      read.get(a); //getting the trash characters
      //reading until the end of file
      while(read.get(a)){
        if(y < MAX_MAZE_Y){
          if(a == 'S'){
            start_maze[i - 1][0] = x;
            start_maze[i - 1][1] = y;
          }
          if(a == EXIT){
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
      cout << "File " << argc[i] << " has been read sucessfully!" << endl << endl;
      read.close(); //closing openned file

      cout << "Test " << i << ". Printing file " << argc[i] << endl << endl;
      cout << "Starting point for maze " << argc[i] << " is (" << start_maze[i - 1][0] << ", " << start_maze[i - 1][1] << ")." << endl;
      printMaze(maze[i - 1]);
      cout << "Please hit enter to continue..." << endl;
      //getchar();
      system("clear");
    }//end of if
    else{
      cout << "Could not open the file with name: " << argc[i] << endl;
    }

    /************************************************************************************************/

    //all the story begins here
    cout << "All the tests for the algorithms will begin as soon as you press enter..." << endl;
    //getchar();
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    double duration_micro;

    //decide here which should work for energy consumption
    bool work_BFS = true;
    bool work_DFS = true;
    bool work_Astar = true;
    bool work_Dijkstra = true;
    bool work_Random = true;




    if(i == 1) write.open("data.txt");
    write << "Statistics for \"" << argc[i] << "\":" << endl << endl;

    if(work_DFS){
      cout << "Press enter for DFS..." << endl;
      //getchar();
      sendFreshTempMaze(maze[i - 1], tmpMaze);
      t1 = high_resolution_clock::now();
      DFS(start_maze[i-1][0],start_maze[i-1][1],tmpMaze);
      t2 = high_resolution_clock::now();
      printMaze(tmpMaze);
      duration_micro = duration_cast<microseconds>( t2 - t1 ).count();
      std::cout << "The time of the process took " << duration_micro << " microsecond(s)." << std::endl;
      write << "DFS results:      " << duration_micro << " microsecond(s)." << endl;
      microseconds_holder[i - 1][0] = duration_micro;
    }


    if(work_BFS){
      cout << "Press enter for BFS..." << endl;
      //getchar();
      sendFreshTempMaze(maze[i - 1], tmpMaze);
      t1 = high_resolution_clock::now();
      BFS(start_maze[i-1][0],start_maze[i-1][1],tmpMaze);
      t2 = high_resolution_clock::now();
      printMaze(tmpMaze);
      duration_micro = duration_cast<microseconds>( t2 - t1 ).count();
      std::cout << "The time of the process took " << duration_micro << " microsecond(s)." << std::endl;
      write << "BFS results:      " << duration_micro << " microsecond(s)." << endl;
      microseconds_holder[i - 1][1] = duration_micro;
    }


    if(work_Astar){
      cout << "Press enter for A*" << endl;
      //getchar();
      sendFreshTempMaze(maze[i - 1], tmpMaze);
      t1 = high_resolution_clock::now();
      Astar(start_maze[i-1][0],start_maze[i-1][1],tmpMaze, end_maze[i - 1]);
      t2 = high_resolution_clock::now();
      printMaze(tmpMaze);
      duration_micro = duration_cast<microseconds>( t2 - t1 ).count();
      std::cout << "The time of the process took " << duration_micro << " microsecond(s)." << std::endl;
      write << "A* results:       " << duration_micro << " microsecond(s)." << endl;
      microseconds_holder[i - 1][2] = duration_micro;
    }


    if(work_Dijkstra){
      cout << "Press enter for Dijkstra..." << endl;
      //getchar();
      sendFreshTempMaze(maze[i - 1], tmpMaze);
      t1 = high_resolution_clock::now();
      Djikstra(start_maze[i-1][0],start_maze[i-1][1],tmpMaze);
      t2 = high_resolution_clock::now();
      printMaze(tmpMaze);
      duration_micro = duration_cast<microseconds>( t2 - t1 ).count();
      std::cout << "The time of the process took " << duration_micro << " microsecond(s)." << std::endl;
      write << "Dijsktra results: " << duration_micro << " microsecond(s)." << endl;
      microseconds_holder[i - 1][3] = duration_micro;
    }



    if(work_Random){
      cout << "Press enter for random..." << endl;
      //getchar();
      sendFreshTempMaze(maze[i - 1], tmpMaze);
      t1 = high_resolution_clock::now();
      start_random_traversing_in_maze(tmpMaze,start_maze[i - 1][0],start_maze[i - 1][1]);
      t2 = high_resolution_clock::now();
      printMaze(tmpMaze);
      duration_micro = duration_cast<microseconds>( t2 - t1 ).count();
      std::cout << "The time of the process took " << duration_micro << " microsecond(s)." << std::endl;
      write << "Random results:   " << duration_micro << " microsecond(s)." << endl;
      microseconds_holder[i - 1][4] = duration_micro;
    }


    cout << "All algorithms made their first cycle. Please hit enter to continue to next maze..." << endl;
    //getchar();
    if(i == 10){
      write << endl << "Total of all 10:" << endl << endl;

      double sum_of_microseconds;
      for(int i = 0;i < 5;i++){
        sum_of_microseconds = 0;
        for(int j = 0;j < 10;j++){
          sum_of_microseconds += microseconds_holder[j][i];
        }
        if(i == 0) write << "DFS total:      " << sum_of_microseconds/10 << " microseconds" << endl;
        if(i == 1) write << "BFS total:      " << sum_of_microseconds/10 << " microseconds" << endl;
        if(i == 2) write << "A* total:       " << sum_of_microseconds/10 << " microseconds" << endl;
        if(i == 3) write << "Dijkstra total: " << sum_of_microseconds/10 << " microseconds" << endl;
        if(i == 4) write << "Random total:   " << sum_of_microseconds/10 << " microseconds" << endl;
      }
      write << "End of file" << endl;
      write.close();//file will be closed here
    }
    /************************************************************************************************/
  }//end of main for
  cout << "Exited successfuly!" << endl << endl;
  return 0;
}

void DFS(int x, int y, char Maze[MAX_MAZE_X][MAX_MAZE_Y]){
  int numberOfDirections;
  int U,L,D,R;
  stack<int> xStack;
  stack<int> yStack;
  while(Maze[x][y] != EXIT && Maze[x][y-multiplerY] != EXIT && Maze[x][y+multiplerY] != EXIT && Maze[x-multiplerX][y] != EXIT && Maze[x+multiplerX][y] != EXIT){
    numberOfDirections = 0;
    U = L = D = R = 0;
    if(Maze[x][y-multiplerY]== ' '){
      U = 1;
      //Up
      numberOfDirections++;
    }
    if(Maze[x-multiplerX][y]== ' '){
      L = 1;
      //Left
      numberOfDirections++;
    }
    if(Maze[x][y+multiplerY]== ' '){
      D = 1;
      //Down
      numberOfDirections++;
    }
    if(Maze[x+multiplerX][y]== ' '){
      R = 1;
      //Right
      numberOfDirections++;
    }
    if(numberOfDirections==0){
      x = xStack.top();
      xStack.pop();
      y = yStack.top();
      yStack.pop();
    }
    else if(numberOfDirections==1){
      x = x + (R-L) * multiplerX;
      y = y + (D-U) * multiplerY;
      Maze[x][y]=WALKER;
    }
    else if(numberOfDirections>1){
      xStack.push(x);
      yStack.push(y);
      if(U) y -= multiplerY;
      else if(R) x += multiplerX;
      else if(D) y += multiplerY;
      else if(L) x -= multiplerX;
      Maze[x][y]=WALKER;
    }
  }
}

void BFS(int x, int y, char Maze[][MAX_MAZE_Y]){
  queue<int> xQue;
  queue<int> yQue;
  int U,L,D,R;
  int numberOfDirections;
  while(Maze[x][y] != EXIT && Maze[x][y-1] != EXIT && Maze[x][y+1] != EXIT && Maze[x-1][y] != EXIT && Maze[x+1][y] != EXIT){
    numberOfDirections = 0;
    U = L = D = R = 0;
    if(Maze[x][y-multiplerY] == ' '){
      U = 1;
      //Up
      numberOfDirections++;
    }
    if(Maze[x-multiplerX][y] == ' '){
      L = 1;
      //Left
      numberOfDirections++;
    }
    if(Maze[x][y+multiplerY] == ' '){
      D = 1;
      //Down
      numberOfDirections++;
    }
    if(Maze[x+multiplerX][y] == ' '){
      R = 1;
      //Right
      numberOfDirections++;
    }
    if(numberOfDirections==0){
      x=xQue.front();
      xQue.pop();
      y=yQue.front();
      yQue.pop();
    }
    else if(numberOfDirections==1){
      x=x+(R-L)*multiplerX;
      y=y+(D-U)*multiplerY;
      Maze[x][y]=WALKER;
    }
    else if(numberOfDirections>1){
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
      Maze[x][y]=WALKER;
    }
  }
}

void Astar(int x, int y, char Maze[][MAX_MAZE_Y], int end[][2]){
  priority_queue<node,vector<node>,comp> open;
  node tmp;
  tmp.gScore = 0;
  tmp.hScore = 0;
  tmp.fScore = 0;
  tmp.x = x;
  tmp.y = y;
  open.push(tmp);
  Maze[tmp.x][tmp.y] = WALKER;

  node cameFrom;

  int cost = 0;
  int heuristic;
  int g[MAX_MAZE_X][MAX_MAZE_Y];
  for(int i=0;i < MAX_MAZE_X;i++){
    for(int j=0;j < MAX_MAZE_Y;j++){
      g[i][j] = -1;
    }
  }
  int i;
  int direction[4][2];
  direction[0][0]=multiplerX;
  direction[0][1]=0;
  direction[1][0]=-multiplerX;
  direction[1][1]=0;
  direction[2][0]=0;
  direction[2][1]=multiplerY;
  direction[3][0]=0;
  direction[3][1]=-multiplerY;
  while(Maze[tmp.x][tmp.y]!=EXIT){
    //neighbours
    if(!open.empty()){
      tmp=open.top();
      open.pop();
      if(Maze[tmp.x][tmp.y]!=EXIT)
        Maze[tmp.x][tmp.y]='c';
    }
    cost = tmp.gScore+1;
    for(int k=0;k<4;k++){
      if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]==WALKER && cost<g[tmp.x+direction[k][0]][tmp.y+direction[k][1]]){
        Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=' ';
      }
      else if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=='c' && cost<g[tmp.x+direction[k][0]][tmp.y+direction[k][1]]){
        Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=' ';
      }
      else if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!=WALKER && Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!='c' && Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!=WALLTYPE){
        g[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=cost;
        if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!=EXIT)
            Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=WALKER;
        tmp.gScore=cost;
        heuristic = 9999;
        for(int k=0;k<10;k++){
          i=abs(x-end[k][0])+abs((y-multiplerY)/2-end[k][1]);
          if(i<heuristic)heuristic=i;
        }
        tmp.hScore=heuristic;
        tmp.fScore=cost+tmp.hScore;
        tmp.x=tmp.x+direction[k][0];
        tmp.y=tmp.y+direction[k][1];
        open.push(tmp);
        tmp.x=tmp.x-direction[k][0];
        tmp.y=tmp.y-direction[k][1];
      }
    }
    //system("sleep 0.2");
    //printMaze(Maze);
  }
}

void Djikstra(int x,int y,char Maze[MAX_MAZE_X][MAX_MAZE_Y]){
  priority_queue<node,vector<node>,comp> open;
  node tmp;
  tmp.gScore=0;
  tmp.fScore=0;
  tmp.x=x;
  tmp.y=y;
  open.push(tmp);
  Maze[tmp.x][tmp.y]=WALKER;

  int cost=0;
  int heuristic=0;
  int g[MAX_MAZE_X][MAX_MAZE_Y];
  g[x][y]=0;
  for(int i=0;i<MAX_MAZE_X;i++)
    for(int j=0;j<MAX_MAZE_Y;j++)
      g[i][j]=-1;

  int direction[4][2];
  direction[0][0]=multiplerX;
  direction[0][1]=0;
  direction[1][0]=-multiplerX;
  direction[1][1]=0;
  direction[2][0]=0;
  direction[2][1]=multiplerY;
  direction[3][0]=0;
  direction[3][1]=-multiplerY;
  while(Maze[tmp.x][tmp.y]!=EXIT){
    //neighbours
    if(!open.empty()){
      tmp=open.top();
      open.pop();
      if(Maze[tmp.x][tmp.y]!=EXIT)
        Maze[tmp.x][tmp.y]='c';
    }
    cost = tmp.gScore+1;
    for(int k=0;k<4;k++){
      if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]==WALKER && cost<g[tmp.x+direction[k][0]][tmp.y+direction[k][1]]){
        Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=' ';
      }
      else if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=='c' && cost<g[tmp.x+direction[k][0]][tmp.y+direction[k][1]]){
        Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=' ';
      }
      else if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!=WALKER && Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!='c' && Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!=WALLTYPE){
        g[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=cost;
        if(Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]!=EXIT)
            Maze[tmp.x+direction[k][0]][tmp.y+direction[k][1]]=WALKER;
        tmp.gScore=cost;
        heuristic = 0;
        tmp.hScore=heuristic;
        tmp.fScore=cost+tmp.hScore;
        tmp.x=tmp.x+direction[k][0];
        tmp.y=tmp.y+direction[k][1];
        open.push(tmp);
        tmp.x=tmp.x-direction[k][0];
        tmp.y=tmp.y-direction[k][1];
      }
    }
    //system("sleep 0.2");
    //printMaze(Maze);
  }
}

void start_random_traversing_in_maze(char Maze[][MAX_MAZE_Y], int start_x, int start_y){
  int x = start_x; //not necessary
  int y = start_y; //not necessary
  pair <int,int> paied_coordinates;
  stack <pair<int,int> > decisions;
  int decision_point;
  bool left, right, up, down;
  int random_go[4]; // [0] left [1] down [2] right [3] up

  while(true){
    decision_point = 0;
    up = down = right = left = false;
    /***************************************************CHECKER***************************************************/
    //right
    if((Maze[x][y + multiplerY] != WALLTYPE && Maze[x][y + multiplerY] != WALKER && Maze[x][y + multiplerY] != START) && y <= MAX_MAZE_Y){
      decision_point++;
      right = true;
    }

    //down
    if((Maze[x + multiplerX][y] != WALLTYPE && Maze[x + multiplerX][y] != WALKER && Maze[x + multiplerX][y] != START) && x <= MAX_MAZE_X){
      decision_point++;
      down = true;
    }

    //left
    if((Maze[x][y - multiplerY] !=  WALLTYPE && Maze[x][y - multiplerY] !=  WALKER && Maze[x][y - multiplerY] !=  START) && y > 0){
      decision_point++;
      left = true;
    }

    //up
    if ((Maze[x - multiplerX][y] != WALLTYPE && Maze[x - multiplerX][y] != WALKER && Maze[x - multiplerX][y] != START)  && x > 0){
      decision_point++;
      up = true;
    }

    if(Maze[x][y + multiplerY] == EXIT || Maze[x + multiplerX][y] == EXIT || Maze[x][y - multiplerY] ==  EXIT || Maze[x - multiplerX][y] == EXIT){
      break; //since it is found breaking out the loop
    }
    /*************************************************************************************************************/

    //this means that there a decision point has been occured!
    if(decision_point > 1){
      paied_coordinates = make_pair(x, y);
      decisions.push(paied_coordinates);
    }

    bool control = true;
    while(control){
      if(right == false && left == false && up == false && down == false){
        paied_coordinates = decisions.top(); //popping the element
        decisions.pop();//deleting the popped element
        x = paied_coordinates.first;
        y = paied_coordinates.second;
        break; //breaking out the loop
      }
      //random direction selection between (1 - 4)
      int random_direction = 1 + rand() % 4;
      //looking for right
      if(random_direction == 1 && right){
        y += multiplerY;
        Maze[x][y] = WALKER;
        control = false;
      }
      //looking for down
      else if(random_direction == 2 && down){
        Maze[++x][y] = WALKER;
        control = false;
      }
      //looking for left
      else if(random_direction == 3 && left){
        y -= multiplerY;
        Maze[x][y] = WALKER;
        control = false;
      }
      //looking up
      else if(random_direction == 3 && up){
        Maze[--x][y] = WALKER;
        control = false;
      }
    }
    //system("sleep 0.2");
    //printMaze(Maze);
  }
}

void sendFreshTempMaze(char maze[][MAX_MAZE_Y], char temporaryMaze[][MAX_MAZE_Y]){
  for(int i = 0;i < MAX_MAZE_X;i++){
    for(int j  = 0;j < MAX_MAZE_Y;j++){
      temporaryMaze[i][j] = maze[i][j];
    }
  }
}

void printMaze(char maze[MAX_MAZE_X][MAX_MAZE_Y]){
    system("clear");
    for(int i = 0;i < MAX_MAZE_X;i++){
      for(int j = 0; j < MAX_MAZE_Y;j++){
        cout << maze[i][j];
      }
      cout << endl;
    }

}
