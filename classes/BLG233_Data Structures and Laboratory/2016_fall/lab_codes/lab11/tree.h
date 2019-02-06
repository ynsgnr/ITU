
struct node {
    int number;
    node *left;
    node *right;
    node *next;
};
struct tree {
       node *root;
       void add(int);
       void createTree();
       int nodecount;
       int sum;
       void printPostorder(node*,int);
       int findNumNode(node *);
       int findMax(node *);
       int findMin(node*);
       int calculateDepth(node *);
};
struct Queue {
       node *front;
       node *back;
       void create();
       void close();
       bool isempty();
       void enqueue(node*);
       node* dequeue();
};
struct Stack{
    	node *head;
    	void create();
    	void close();
    	void push(node*);
    	node* pop();
    	bool isempty();
};
