#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "labyrinth.h"
#include "functions.h"
#define SMALL_SCALE 100
#define MEDIUM_SCALE 1000
#define LARGE_SCALE 10000

using namespace std;

void print_list();//function prototype

int main(){
	functions func;
	lab **labyrinth_S = NULL, **labyrinth_M = NULL, **labyrinth_L = NULL;
	bool loop = true;
	char choice;
	while(loop){
		print_list();
		cin >> choice;
		cin.ignore(10,'\n');
		switch(choice){
			case 'G':case 'g':
				system("clear");//for linux and macOS
				//system("cls");//for windows
				cout << "Please enter choose the size of your labyrinth." << endl;
				cout << "1: for small (100x100)" << endl;
				cout << "2: for medium (1000x1000)" << endl;
				cout << "3: for large (10000x10000)" << endl;
				cout << "Enter your choice:";
				int size;
				cin >> size;
				cin.ignore(10,'\n');
				if(size == 1){
					if(labyrinth_S == NULL){
						labyrinth_S = new lab*[SMALL_SCALE];
						for(int i = 0;i < SMALL_SCALE;++i) labyrinth_S[i] = new lab[SMALL_SCALE];
						func.labyrinth_initializer(labyrinth_S, SMALL_SCALE);
					}
					else{
						cout << "Memory for small labyrinth was already allocated." << endl;
						system("sleep 1");
					}
				}
				else if(size == 2){
					if(labyrinth_M == NULL){
						labyrinth_M = new lab*[MEDIUM_SCALE];
						for(int i = 0; i < MEDIUM_SCALE; ++i) labyrinth_M[i] = new lab[MEDIUM_SCALE];
						func.labyrinth_initializer(labyrinth_M, MEDIUM_SCALE);
					}
					else{
						cout << "Memory for small labyrinth was already allocated." << endl;
						system("sleep 1");
					}
				}
				else if(size == 3){
					if(labyrinth_L == NULL){
						labyrinth_L = new lab*[LARGE_SCALE];
						for(int i = 0;i < LARGE_SCALE;++i) labyrinth_S[i] = new lab[LARGE_SCALE];
						func.labyrinth_initializer(labyrinth_L, LARGE_SCALE);
					}
					else{
						cout << "Memory for small labyrinth was already allocated." << endl;
						system("sleep 1");
					}

				}
				else{
					cout << "Wrong choice entered. Return to main menu and try again. Hit enter to continue..." << endl;
					getchar();
				}
				break;
			case 'C':case 'c':
				if(labyrinth_S != NULL || labyrinth_M != NULL || labyrinth_L != NULL){
					if(labyrinth_S != NULL){
						cout << "Deleting small labyrinth..." << endl;
						func.clear_memory(labyrinth_S, SMALL_SCALE);
						cout << "Memory for small labyrinth was successfully deallocated." << endl;
						labyrinth_S = NULL;
					}
					if(labyrinth_M != NULL){
						cout << "Deleting medium labyrinth..." << endl;
						func.clear_memory(labyrinth_M, MEDIUM_SCALE);
						cout << "Memory for medium labyrinth was successfully deallocated." << endl;
						labyrinth_M = NULL;
					}
					if(labyrinth_L != NULL){
						cout << "Deleting large labyrinth..." << endl;
						func.clear_memory(labyrinth_L, LARGE_SCALE);
						cout << "Memory for large labyrinth was successfully deallocated." << endl;
						labyrinth_L = NULL;
					}
				}
				else
					cout << "No deallocation made since no allocation was made." << endl;
				cout << "Hit enter to return to main menu..." << endl;
				getchar();

				break;
			case 'E':case 'e':
				loop = false;
				break;
			default:
				cout << "Wrong choice entered. Hit enter to continue..." << endl;
				getchar();
				break; 
		}//end of switch
	}//end of while
	return 0;
}//end of main

void print_list(){
	system("clear");//for linux and macOS
	//system("cls");//for windows
	cout << "***********************************************************************" << endl;
	cout << "Welcome to the testing environment of different path-finder algorithms." << endl;
	cout << "***********************************************************************" << endl;
	cout << "* G: For generating random maze.                                      *" << endl;
	cout << "* C: For clear memory.												   *" << endl;
	cout << "* E: For exit.  													   *" << endl;
	cout << "***********************************************************************" << endl << endl;
	cout << "Enter choice:";
}


