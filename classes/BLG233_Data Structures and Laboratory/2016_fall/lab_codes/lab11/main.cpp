#include <iostream>
#include <ctime>
#include <fstream>
#include "tree.h"
#define N 10
using namespace std;
int BFScount=0;
int DFScount=0;
void BFS(node *root, int num){
     Queue Q;
     Q.create();
     Q.enqueue(root);
     node* u;
     while(!Q.isempty()){
           u=Q.dequeue();            
           if(u->left) Q.enqueue(u->left);
           if(u->right) Q.enqueue(u->right);
           cout << u->number << " ";
           BFScount++;
           if(num==u->number){
                              cout << "bulundu";
                              break;
           }
     }
}

void DFS(node *root, int num){
     Stack S;
     S.create();
     S.push(root);
     node* u;
     while (!S.isempty()){
           u=S.pop();
           if(u->right) S.push(u->right);
           if(u->left) S.push(u->left);
           cout << u->number << " ";
           DFScount++;
           if(num==u->number){
                              cout << "bulundu";
                              break;
           }
     }
}

void Stack::create(){
     head=NULL;
}

void Stack::close(){
	node *p;
	while (head){
		p = head;
		head = head->next;
		//delete [] p->data;
		delete p;
	}
}

void Stack::push(node *newdata){
	node *newnode = new node;
	newnode = newdata;
	newnode->number = newdata->number;
	newnode->next = head;
	head = newnode;
}

node *Stack::pop(){
	if (isempty())
		return NULL;
	node *topnode = head;
	head = head->next;
	//delete topnode;
	return topnode;
}
bool Stack::isempty(){
	return (head == NULL);
}

void Queue::enqueue(node* newdata){
	node *newnode = new node;
	newnode = newdata;
	newnode->left=newdata->left;
	newnode->right=newdata->right;
	newnode->number=newdata->number;
	newnode->next = NULL;
	if ( isempty() ) { // first element?
		back = newnode;
		front = back;
	}
	else {
		back->next = newnode;
		back = newnode;
	}
}

node *Queue::dequeue() {
	node *topnode;
	topnode = front;
	front = front->next;
	//delete topnode;
	return topnode;
}

bool Queue::isempty() {
	return front == NULL;
}

void Queue::create(){
	front = NULL; back = NULL;
}
void Queue::close(){
	node *p;
	while (front) {
		p = front;
		front = front->next;
		//delete [] p->data;
		delete p;
	}
}
int b =0;
void tree::add(int toadd){  //Binary tree, Binary search tree değil!!!!  (d-1) boşken (d)'ye eleman eklemez
             node *traverse, *newnode;
             traverse = root;
             int comparison;
             bool added = false;
             newnode = new node;
             newnode->number=toadd;
             newnode->left = NULL;
             newnode->right = NULL;
             if (root == NULL){//first node being added
                root = newnode;
                return;
             }
             if(root->left==NULL){
                                  root->left=newnode;
                                  return;
             }
             if(root->right==NULL){
                                  root->right=newnode;
                                  return;
             }
             int l,r;
             while(findNumNode(traverse)>2){
                             b=0;
                             l=findNumNode(traverse->left);
                             b=0;
                             r=findNumNode(traverse->right);
                             b=0;
                            if (l < r) traverse = traverse->left;
                            else if (l>r) traverse = traverse->right;
                            else if (l==r) traverse = traverse->left;
             }
             if(traverse->left==NULL){
                                      traverse->left=newnode;
                                      return;
             }
             if(traverse->right==NULL){
                                      traverse->right=newnode;
                                      return;
             }
             

}
     
void tree::createTree(){
     root=NULL;
     nodecount=0;
     int array[N];
     for(int i=0; i<N; i++){
             x:   //sayı tekrarı kapalı
             array[i]=rand() % 20+1; //random sayı aralığını burdan değiştir
             for(int j=i-1; j>=0; j--){
                     if(array[j]==array[i]) goto x;}
             add(array[i]);
     }
}

int main(){
    tree tree;
    srand(time(0));
    int input;
    cout << "Enter number to find a node in Tree: ";
    cin >> input;
    tree.createTree();
    cout << endl<<"Postorder:   ";
    tree.printPostorder(tree.root, input);
    cout << endl<< "step: "<<tree.nodecount-1 << endl<<"BFS: ";
    BFS(tree.root,input);
    cout << endl<< "step: "<<BFScount-1<<endl<< "DFS: ";
    DFS(tree.root,input);
    cout <<endl << "step: "<<DFScount-1 <<endl;    
    system("pause");
}
bool a=false;
void tree::printPostorder(node *nptr, int num) {
    if (nptr) {
        printPostorder(nptr->left, num);
        if(a) return;
        printPostorder(nptr->right, num);
        if(a) return;
        cout << nptr->number << " ";
        nodecount++;
                        if(num==nptr->number){
                              cout << "bulundu";
                              a=true;
                              return;
                              }
    }
}
int tree::findNumNode(node* ptr){//geliştir
    if(ptr){
            b++;
            findNumNode(ptr->left);
            findNumNode(ptr->right);
    }
    return b;
}

