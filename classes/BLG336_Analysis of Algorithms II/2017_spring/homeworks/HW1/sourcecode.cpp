#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* compiled with command:
* g++ sourcecode.cpp
*/

class stepNode {
public:
  //location of each entity (0:left side, 1: rigth side):
  int farmer, fox, rabbit, carrots;

  stepNode();
  bool isValid();
  void printNode();
};

stepNode::stepNode(){
  farmer=1;
  fox=0;
  rabbit=0;
  carrots=0;
}

bool stepNode::isValid(){
  if(fox==rabbit && farmer!=rabbit){
    return false;
  }
  if(rabbit==carrots && farmer!=rabbit){
    return false;
  }
  return true;
}

void stepNode::printNode(){
  if(farmer==0){
    std::cout << "Farmer ";
  }
  if(fox==0){
    std::cout << "Fox ";
  }
  if(rabbit==0){
    std::cout << "Rabbit ";
  }
  if(carrots==0){
    std::cout << "Carrots";
  }
  std::cout << " || ";
  if(farmer==1){
    std::cout << "Farmer ";
  }
  if(fox==1){
    std::cout << "Fox ";
  }
  if(rabbit==1){
    std::cout << "Rabbit ";
  }
  if(carrots==1){
    std::cout << "Carrots";
  }
}

int main(int argc, char *argv[]) {

  clock_t startTime;
  clock_t endTime;

  int i,j,k,l,m,n,o,t;
  int visitedNodes, nodesKept;

  int layers[10][3]; //BFS Layers
  int layerCount[10]; //Counter for layer elements
  stepNode nodes[32]; //All possible nodes
  bool discovered[32]; //Dıscovered for both BFS and DFS
  int stack[20]; //Stack for dfs
  int head; //head of stack;
  int adjencyList[32][3]; //since graph is very small linked list is not applied
  int DFSTree[32][3]; //Tree for DFS

  for(i=0;i<32;i++){
    for(j=0;j<3;j++){
      adjencyList[i][j]=-1;
    }
  }

  if(argc!=2){
    std::cout << "Wrong Input"<<"\n";
    return -1;
  }

  //Constracting graph
  //This part built with for loops in order to
  //increase readability and scalability
  m=0;
  for (i=0;i<2;i++){
    for (j=0;j<2;j++){
      for (k=0;k<2;k++){
        for (l=0;l<2;l++){
          nodes[m].farmer=i;
          nodes[m].fox=j;
          nodes[m].rabbit=k;
          nodes[m].carrots=l;
          for(n=0;n<32;n++){
            if(n!=m && nodes[m].isValid() && nodes[n].isValid() &&
              nodes[m].farmer!=nodes[n].farmer){
              t=nodes[m].fox==nodes[n].fox;
              t+=nodes[m].rabbit==nodes[n].rabbit;
              t+=nodes[m].carrots==nodes[n].carrots;
              //minimum 2 of these must be true to have an edge between
              if(t>=2){
                o=0;
                while(adjencyList[m][o]!=-1 && o<3){
                  o++;
                }
                adjencyList[m][o]=n;
                o=0;
                while(adjencyList[n][o]!=-1 && o<3){
                  o++;
                }
                adjencyList[n][o]=m;
              }
            }
          }
          discovered[m]=false;
          m++;
        }
      }
    }
  }

  /*
  //Print adjencyList
  for(i=0;i<32;i++){
    std::cout << i << " " << discovered[j] << " - ";
    for(j=0;j<3;j++){
      std::cout << adjencyList[i][j] << ' ';
    }
    nodes[i].printNode();
    std::cout << '\n';
  }
  */

  if(strcmp(argv[1],"bfs")==0 || strcmp(argv[1], "BFS")==0){
    std::cout << "Algorithm: BFS"<<"\n";
    visitedNodes=0;
    startTime=clock();

    layerCount[0]=1;
    layers[0][0]=0;
    discovered[0]=true;
    i=0;
    while(i<10 && layerCount[i]!=0){
      layerCount[i+1]=0;
      for(j=0;j<layerCount[i];j++){
        o=0;
        k=0;
        while(o<3 && adjencyList[layers[i][j]][o]!=-1){
          visitedNodes++;
          if(!discovered[adjencyList[layers[i][j]][o]]){
            //nodes[layers[i][j]].printNode();
            //std::cout << '\n';
            //without printing stuff, it shows 0 as time
            discovered[adjencyList[layers[i][j]][o]]=true;
            layers[i+1][k]=adjencyList[layers[i][j]][o];
            k++;
            layerCount[i+1]++;
          }
          o++;
        }
      }
      i++;
    }
    endTime=clock();

    nodesKept=0;
    for(i=0;i<10;i++){
      nodesKept+=layerCount[i];
    }

    std::cout << "Solution:" << '\n';
    i=0;
    while(layerCount[i]!=0){
      nodes[layers[i][0]].printNode();
      std::cout << '\n';
      i++;
    }

    if(i==10)
      std::cout << "Something went wrong. There is more elements than expected." << '\n';
    std::cout << "BFS finished after " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';
  }else if(strcmp(argv[1], "dfs")==0 || strcmp(argv[1], "DFS")==0){
    std::cout << "Algorithm: DFS"<<"\n";
    for(i=0;i<32;i++){
      for(j=0;j<3;j++){
        DFSTree[i][j]=-1;
      }
    }
    startTime=clock();

    head=1;
    stack[0]=-1; //first node do not have a parent
    stack[1]=0;
    while(head!=-1){

      k=stack[head];
      head--;
      l=stack[head];
      head--;

      if(!discovered[k]){
        //nodes[stack[head]].printNode();
        //std::cout << '\n';
        //without printing stuff, it shows 0 as time
        discovered[k]=true;

        //Add p(u),u to tree;
        o=0;
        while(DFSTree[k][o]!=-1 && o<3){
          o++;
        }
        DFSTree[k][o]=l;
        if(l!=-1){
          o=0;
          while(DFSTree[l][o]!=-1 && o<3){
            o++;
          }
          DFSTree[l][o]=k;
        }

        o=0;
        while(o<3 && adjencyList[k][o]!=-1){
          visitedNodes++;
          head++;
          stack[head]=k; //push parent first
          head++;
          stack[head]=adjencyList[k][o];
          o++;
        }
      }
      if(nodesKept<head){
        nodesKept=head;
      }
    }

    endTime=clock();

    nodesKept++;//stack starts from zero
    nodesKept=nodesKept/2; //each push or pop uses two space

    std::cout << "Solution:" << '\n';

    for(i=0;i<32;i++){
      discovered[i]=false;
    }
    i=0;
    j=0;
    while(i!=-1){
      if(!discovered[i]){
        discovered[i]=true;
        nodes[i].printNode();
        std::cout << '\n';
      }
      k=i;
      i=DFSTree[i][j];
      if(!discovered[i]){
        j=0;
      }else{
        i=k;
        j++;
      }
    }

    std::cout << "DFS finished after " << endTime-startTime << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';
  }else{
    std::cout << "Wrong Input"<<"\n";
    return -1;
  }

  std::cout << "Visited Nodes: " << visitedNodes << '\n';
  std::cout << "Nodes kept in memory: " << nodesKept << '\n';

  return 0;
}
