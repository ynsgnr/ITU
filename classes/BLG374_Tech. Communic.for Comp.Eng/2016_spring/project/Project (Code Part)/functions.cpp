#include <iostream>
#include "functions.h"
using namespace std;

//write functions specifications here :D

void functions::labyrinth_initializer(lab **maze, int size){
	for(int i = 0;i < size;i++){
		for(int j = 0; j < size;j++){
			maze[i][j].right = maze[i][j].left = maze[i][j].up = maze[i][j].down = false;
			maze[i][j].value = ' '; // this is the actual path which is empty at the beginning and will be filled when it is visited
			maze[i][j].visited = false;
		}	
	}
}

void functions::clear_memory(lab **maze,int size){
	for(int i = 0;i < size;i++){
		delete[] maze[i];
	}
	delete[] maze;
}