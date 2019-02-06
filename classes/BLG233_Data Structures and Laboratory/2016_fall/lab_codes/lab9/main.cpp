#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace std;

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* Date: 07.12.2016
*/

struct node {
	int number;
	node *left;
	node *right;
};

struct tree {
node *root;

//TODO add functions here
};

tree directory;

node* findEmptySpace(node* n,int* i){
	int t1,t2;
	node * tmp1, * tmp2;

	if(n->right==NULL || n->left==NULL){
		return n;
	}
	else {
		(*i)++;
		t2=*i;
		tmp1=findEmptySpace(n->right,i);
		t1=*i;
		*i=t2;
		tmp2=findEmptySpace(n->left,i);
		t2=*i;
		if (t1<=t2) return tmp1;
		else return tmp2;
	}
}

int createTree(){
	/*Create a random integer array (size of N, values should also be between 1 and N)
	and insert each element of the array to your binary tree. You should not add
	an element to the depth (d) if depth (d-1) has an empty spot.*/

	int N,smallest,temp,k;
	node *p;
	node *tmp;

	cout<<"Enter size and max number:"<<endl;
	cin>>N;

	//create first element

	p = new node;
	p->number = rand()%N+1;
	p->left = p->right = NULL;

	directory.root=p;

	for(int i=1;i<N;i++){
		k=0;
		p = findEmptySpace(directory.root,&k);
		tmp=new node;
		tmp->number=rand()%N+1;
		tmp->left = tmp->right = NULL;
		if(p->right==NULL) p-> right=tmp;
		else if (p->left==NULL) p->left=tmp;
	}

	return N;
}

void removeTree(node *p){
 //Removes all of the tree nodes from the memory.
	if(p->right!=NULL && p->left==NULL){
		removeTree(p->right);
		p->right=NULL;
	}
	if(p->right==NULL && p->left!=NULL){
		removeTree(p->left);
		p->left=NULL;
	}
	if(p->right!=NULL && p->left!=NULL){
		removeTree(p->right);
		p->right=NULL;

		removeTree(p->left);
		p->left=NULL;
	}
	if(p->right==NULL && p->left==NULL){
		delete p;
	}
}

void printPreorder(node* nptr){
	//Prints the contents of the binary tree to the screen in preorder.
	if (nptr) {
		cout << nptr->number << " ";
		printPreorder(nptr->left);
		printPreorder(nptr->right);
	}
}

void printInorder(node* nptr){
	//Prints the contents of the binary tree to the screen in inorder.
	if (nptr) {
		printInorder(nptr->left);
		cout << nptr->number << " ";
		printInorder(nptr->right);
	}
}

void printPostorder(node* nptr){
	//Prints the contents of the binary tree to the screen in postorder.
	if (nptr) {
		printPostorder(nptr->left);
		printPostorder(nptr->right);
		cout << nptr->number << " ";
	}
}

int findMax(node* n,int max){
	//Finds the maximum value in the binary tree and and returns it.
	if (n) {
		max=findMax(n->left,max);
		max=findMax(n->right,max);
		if((n->number)>max)	return (n->number);
	}
	return max;
}

int findMin(node* n,int min){
	//Finds the minumum value in the binary tree and and returns it.
	if (n) {
		min=findMin(n->left,min);
		min=findMin(n->right,min);
		if(n->number<min) return (n->number);
	}
	return min;
}

int findNumNode(node *n,int i){
	//Finds the number of the nodes in the binary tree and returns this value.
	if (n) {
		i++;
		i=i+findNumNode(n->right,0);
		i=i+findNumNode(n->left,0);
		return i;
	}
	else return 0;
}

int findNumLeaf(node *n,int i){
	//Finds the number of the leaves in the binary tree and returns this value.
	if (n) {
		i=i+findNumLeaf(n->right,0);
		i=i+findNumLeaf(n->left,0);
		if(n->right==NULL && n->right==NULL)
			i++;
		return i;
	}
	else return 0;
}

int calculateDepth(node* n, int i){
	//Calculates the depth of the binary tree and returns this value.
	int t1,t2;
	if(n==NULL){
		return i;
	}
	else {
		i++;
		t1=calculateDepth(n->right,i);
		t2=calculateDepth(n->left,i);
		if (t1>t2) return t1;
		else return t2;
	}
}

int calculateSum(node *n,int i){
	//Calculates the summation of the values in the binary tree and returns this value.
	if (n) {
		i=i+calculateSum(n->right,0);
		i=i+calculateSum(n->left,0);
		return i+n->number;
	}
	else return 0;
}

long calculateAverage(node *n){
	//Calculates the average of the values that are stored in the nodes of the binary tree and returns this value.
	return (long)(calculateSum(n,0)/findNumNode(n,0);
}

int main(){
	srand (time(NULL));
	int N;
	N=createTree();

	cout<<"Preorder: ";
	printPreorder(directory.root);
	cout << endl;

	cout<<"Inorder:";
	printInorder(directory.root);
	cout<<endl;

	cout<<"Postorder:";
	printPostorder(directory.root);
	cout<<endl;

	cout<<"Max: "<<findMax(directory.root,0)<<endl;

	cout<<"Min: "<<findMin(directory.root,N)<<endl;

	cout<<"Number of node: "<<findNumNode(directory.root,0)<<endl;

	cout<<"Number of leaf: "<<findNumLeaf(directory.root,0)<<endl;

	cout<<"Depth: "<<calculateDepth(directory.root,0)<<endl;

	cout<<"Sum: "<<calculateSum(directory.root,0)<<endl;

	cout<<"Avg: "<<calculateAverage(directory.root)<<endl;

	removeTree(directory.root);

	return 0;
}
