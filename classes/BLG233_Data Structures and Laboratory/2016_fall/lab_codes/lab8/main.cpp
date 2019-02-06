#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace std;

#define MAZESIZE 10

typedef struct cell
{
bool left, right, up, down; // right = false when a wall does not exist otherwise, right = true means there is a wall
char val; // initially this is empty (' '), when the cell is used to reach the exit, this becomes 'o'
bool visited; // this variable will be used while generating maze randomly (look the pseudo code for further information)
};
cell m[MAZESIZE][MAZESIZE]; // this is the maze

void print(cell[][MAZESIZE]);

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 30.11.2016
*/

void solve();
void generate();
bool thereIsUnvisited();

typedef struct stack
{
	stack* prev;
	int x;
	int y;
};

stack* cellStack;
int stackCounter=0;

int main (){
	cellStack = new stack;
	cout<<cellStack<<endl;
	cellStack->prev=NULL;
	cellStack->x=0;
	cellStack->y=0;

	for(int i = 0; i < MAZESIZE; i++)
		for(int j = 0; j < MAZESIZE; j++){
			m[i][j].up=true;
			m[i][j].down=true;
			m[i][j].left=true;
			m[i][j].right=true;
			m[i][j].val=' ';
			m[i][j].visited=false;
		}

	srand(time(NULL));
	generate();
	solve();
	print(m);
		for(int i = 0; i < MAZESIZE; i++)
		for(int j = 0; j < MAZESIZE; j++){
			m[i][j].up=true;
			m[i][j].down=true;
			m[i][j].left=true;
			m[i][j].right=true;
			m[i][j].val=' ';
			m[i][j].visited=false;
		}
    print(m);
	return 0;

}

void generate(){
	/*
	While there are unvisited cells in the maze
		If the current cell has any neighbours which have not been visited
			Choose randomly one of the unvisited neighbours
			Push the current cell to the stack
			Remove the wall between the current cell and the chosen cell (remind
				that you should modify the related variables in both neighbour cells)
			Make the chosen cell the current cell and mark it as visited
	Else if stack is not empty
		Pop a cell from the stack
		Make it the current cell
	Else
		Pick a random cell, make it the current cell and mark it as visited
		 ____ ___ ____
		|    |i-1|    |
		| j-1| * |j+1 |
		|____|i+1|____|
*/
	int i=0; int j=0;
	int direction;
	stack * tmp;
	while(thereIsUnvisited()){
		if(i>0 && i<MAZESIZE && j>0 && j<MAZESIZE && (!m[i-1][j].visited || !m[i+1][j].visited || !m[i][j-1].visited || !m[i][j+1].visited)){
			cout<<cellStack<<endl;
			direction=rand()%4;
			//push
			tmp=new stack;
			tmp->prev=cellStack;
			tmp->x=j;
			tmp->y=i;
			cellStack=tmp;
			stackCounter++;
			switch(direction){
				case 0:
					//top
					//remove walls
					m[i][j].up=false;
					i--;
					m[i][j].down=false;

					m[i][j].visited=true;
					break;

				case 1:
					//left
					//remove walls
					m[i][j].left=false;
					j--;
					m[i][j].right=false;

					m[i][j].visited=true;
					break;

				case 2:
					//down
					//remove walls
					m[i][j].down=false;
					i++;
					m[i][j].up=false;

					m[i][j].visited=true;
					break;

				case 3:
					//right
					//remove walls
					m[i][j].right=false;
					j++;
					m[i][j].left=false;

					m[i][j].visited=true;
					break;
			}
		}
		else if(stackCounter>0){
			//pop
			j=cellStack->x;
			i=cellStack->y;
			tmp=cellStack;
			cellStack=cellStack->prev;
			delete tmp;
			stackCounter--;
		}
		else{
			i=rand()%MAZESIZE;
			j=rand()%MAZESIZE;
			m[i][j].visited=true;
		}
	}
}

bool thereIsUnvisited(){
	int i=0; int j=0;
	bool notDone=true;
	while(i<MAZESIZE && notDone){
		while(j<MAZESIZE && notDone){
			if(!m[i][j].visited) notDone=false;
			j++;
		}
		i++;
	}
	return !notDone;
}

void solve(){

}

void print(cell m[][MAZESIZE])
{
	for(int i = 1; i < MAZESIZE; i++)
	{
		for(int j = 1; j < MAZESIZE; j++)
		{
			if(m[i][j].up)
				cout << " -";
				else cout << " ";
		}
		cout << endl;
		cout << "|";
		for(int j = 1; j < MAZESIZE; j++)
		{
			if(m[i][j].right)
				cout << m[i][j].val << "|";
			else
				cout << m[i][j].val << " ";
		}
		cout << endl;
	}
	for(int i = 1; i < MAZESIZE; i++)
	{
		if(m[MAZESIZE-1][i].down)
			cout << " -";
	}
	cout << endl;
}
