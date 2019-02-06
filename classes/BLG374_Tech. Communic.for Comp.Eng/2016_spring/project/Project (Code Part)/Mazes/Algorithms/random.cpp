//@author: Korel Chairoula (Hayrullah)
//random.cpp A code that chooses its direction not clockwise, but randomly
#include <iostream>
#include <cstdlib> //srand for random
#include <ctime>   //time for random
#include <stack>   //for stack
#include <utility> //for pair

//please change these according to your design here!!!
#define WALLTYPE '*'
#define WALKER '!'
#define START 'S'
#define EXIT 'E'
#define X_AXIS 1
#define Y_AXIS 1
#define MAX_MAZE_X 51
#define MAX_MAZE_Y 101

using namespace std;

void print_Maze(char [][MAX_MAZE_Y]);                                  //function prototype
void start_random_traversing_in_maze(char [][MAX_MAZE_Y], int, int);   //function prototype


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
    if((Maze[x][y + Y_AXIS] != WALLTYPE && Maze[x][y + Y_AXIS] != WALKER && Maze[x][y + Y_AXIS] != START) && y <= MAX_MAZE_Y){
      decision_point++;
      right = true;
    }

    //down
    if((Maze[x + X_AXIS][y] != WALLTYPE && Maze[x + X_AXIS][y] != WALKER && Maze[x + X_AXIS][y] != START) && x <= MAX_MAZE_X){
      decision_point++;
      down = true;
    }

    //left
    if((Maze[x][y - Y_AXIS] !=  WALLTYPE && Maze[x][y - Y_AXIS] !=  WALKER && Maze[x][y - Y_AXIS] !=  START) && y > 0){
      decision_point++;
      left = true;
    }

    //up
    if ((Maze[x - X_AXIS][y] != WALLTYPE && Maze[x - X_AXIS][y] != WALKER && Maze[x - X_AXIS][y] != START)  && x > 0){
      decision_point++;
      up = true;
    }

    if(Maze[x][y + Y_AXIS] == EXIT || Maze[x + X_AXIS][y] == EXIT || Maze[x][y - Y_AXIS] ==  EXIT || Maze[x - X_AXIS][y] == EXIT){
      cout << "Found!" << endl;
      //emptying stack
      while(!decisions.empty()){
        decisions.top();
        decisions.pop();
      }
      break; //since it is found breaking out the loop
    }
    /*************************************************************************************************************/

    cout << "Current coordinates (" << x <<", "<< y <<")." << endl;
    cout << "Possible walks: " << endl;
    if(left) cout << "Left" << endl;
    if(right) cout << "Right" << endl;
    if(up) cout << "Up" << endl;
    if(down) cout << "Down" << endl;

    //this means that there a decision point has been occured!
    if(decision_point > 1){
      cout << "Decision point occured!" << endl;
      paied_coordinates = make_pair(x, y);
      decisions.push(paied_coordinates);
    }

    cout << "Choosing direction" << endl;

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
        cout << "Right is chosen!" << endl;
        Maze[x][++y] = WALKER;
        control = false;
      }
      //looking for down
      else if(random_direction == 2 && down){
        cout << "Down is chosen!" << endl;
        Maze[++x][y] = WALKER;
        control = false;
      }
      //looking for left
      else if(random_direction == 3 && left){
        cout << "Left is chosen!" << endl;
        Maze[x][--y] = WALKER;
        control = false;
      }
      //looking up
      else if(random_direction == 3 && up){
        cout << "UP is chosen!" << endl;
        Maze[--x][y] = WALKER;
        control = false;
      }
    }
    print_Maze(Maze);//printing the Maze
  }

}

void print_Maze(char Maze[][MAX_MAZE_Y]){
  system("sleep 0.1");
  system("clear");
  for(int i = 0;i < MAX_MAZE_X;i++){
    for(int j = 0; j < MAX_MAZE_Y;j++){
      cout << Maze[i][j];
    }
    cout << endl;
  }
}
