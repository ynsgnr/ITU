#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
* compiled with command:
* g++ sourcecode.cpp
*/

#define  DIMENSIONS 3

float calculateDistance(std::vector<int> coordinates1, std::vector<int> coordinates2);
std::vector< std::vector< std::vector<int> > > drawLine(std::vector< std::vector<int> > spheres ,int count); //Divide
float findClosestPair(std::vector< std::vector<int> > spheres, int count); //Conquer
float findClosestPairAroundLine (std::vector< std::vector<int> > spheres , int count, int line, float distance); //Combine
bool compare(std::vector<int> i,std::vector<int> j);

int distanceCalculatedCount=0;

int main(int argc, char *argv[]) {

  std::fstream file;
  std::string line,tmp;
  int sphereCount,i,j;
  std::vector< std::vector<int> > spheres;

  clock_t startTime;
  clock_t endTime;

  if(argc!=2 && argc!=3){
    std::cout << "Wrong Input"<<"\n";
    return -1;
  }

  file.open(argv[1], std::fstream::in );
  if(file.is_open()){
    getline(file,line);
    sphereCount=atoi(line.c_str());

    spheres.resize(sphereCount);

    i=0;
    while(i<sphereCount){
      getline(file,line);
      //Column number is assumed to be three
      if(line.length()>=5){
        spheres[i].resize(3);

        tmp=line.substr(0, line.find(" "));
        line=line.substr(line.find(" ")+1,line.size());
        spheres[i][0]=atoi(tmp.c_str());

        tmp=line.substr(0, line.find(","));
        line=line.substr(line.find(" ")+1,line.size());
        spheres[i][1]=atoi(tmp.c_str());

        tmp=line.substr(0, line.find(","));
        spheres[i][2]=atoi(tmp.c_str());

        i++;
      }//Empty lines are ignored
    }
  }
  else throw "File not open";

  startTime=clock();

  std::sort(spheres.begin(),spheres.end(),compare);
  float result = findClosestPair(spheres, sphereCount);

  endTime=clock();

  printf("The distance is %f\nNumber of total distance calculations is %d\n",result,distanceCalculatedCount);
  std::cout << "Process finished after " <<  (float)(endTime-startTime) << " clicks and " << (float)(endTime-startTime)/CLOCKS_PER_SEC << " seconds" << '\n';
  std::cout << '\n';

  if(argc==3){
    //Brute force method for testing with small amount of data
    std::vector< std::vector<int> > minPoints(2);
    minPoints[0].resize(3);
    minPoints[1].resize(3);
    float min=999999;
    float d;

    for(i=0;i<sphereCount;i++){
      for(j=0;j<sphereCount;j++){
          d=calculateDistance(spheres[i],spheres[j]);
          if(i!=j && d<min){
            minPoints[0]=spheres[i];
            minPoints[1]=spheres[j];
            min=d;
          }
      }
    }

    printf("Brute Force Method:\n");
    printf("Points:\n%d %d %d\n%d %d %d\nDistance:%f",minPoints[0][0],minPoints[0][1],minPoints[0][2],minPoints[1][0],minPoints[1][1],minPoints[1][2],min);
  }



  return 0;
}

float calculateDistance(std::vector<int> coordinates1, std::vector<int> coordinates2){
  distanceCalculatedCount++;
  float dx=coordinates1[0]-coordinates2[0];
  float dy=coordinates1[1]-coordinates2[1];
  float dz=coordinates1[2]-coordinates2[2];
  return sqrt(dx*dx+dy*dy+dz*dz);
}

float findClosestPair(std::vector< std::vector<int> > spheres, int count){
  int i;
  float result=99999999;
  if(count==3){
    float d1=calculateDistance(spheres[0],spheres[1]);
    float d2=calculateDistance(spheres[0],spheres[2]);
    float d3=calculateDistance(spheres[1],spheres[2]);
    if(d1<d2){
      if(d1<d3){
        //Smallest is d1
        result=d1;
      }else{
        //Smallest is d3
        result=d3;
      }
    }else if(d2<d3){
      //Smallest is d2
      result=d2;
    }else{
      //Smallest is d3
      result=d3;
    }
    return result;
  }else if(count==2){
    return calculateDistance(spheres[0],spheres[1]);
  }else if(count<2){
    return result;
  }

  std::vector< std::vector< std::vector<int> > > divided = drawLine(spheres,count);

  float leftClosest = findClosestPair(divided[0],(divided[0].size()-1));
  float rightClosest = findClosestPair(divided[1],(divided[1].size()-1));

  if(leftClosest<rightClosest){
    result=leftClosest;
  }else{
    result=rightClosest;
  }

  int line = (divided[1][0][0]+divided[0].back()[0])/2;

  //Calculate around line
  float closestAroundLine = findClosestPairAroundLine(spheres,count,line/*line*/,result);
  if(result<closestAroundLine){
    return result;
  }else{
    return closestAroundLine;
  }

}

bool compare(std::vector<int> i,std::vector<int> j){return (i[0]<j[0]);}

std::vector< std::vector< std::vector<int> > > drawLine(std::vector< std::vector<int> > spheres ,int count){
  //Assumed data is sorted
  int i;

  std::vector< std::vector< std::vector<int> > > result(2);
  for(i=0;i<(count/2);i++){
    result[0].push_back(spheres[i]);
  }
  for(i=(count/2);i<count;i++){
    result[1].push_back(spheres[i]);
  }
  return result;
}

float findClosestPairAroundLine (std::vector< std::vector<int> > spheres, int count, int line, float distance){
    int i,j,k,aroundLineCount;
    float result=999999999;
    float d1;
    std::vector< std::vector<int> > aroundLine(count);
    for(i=0;i<count;i++){
      aroundLine[i].resize(3);
    }

    aroundLineCount=0;
    for(i=0;i<count;i++){
      if(abs(spheres[i][0]-line)<=distance){
        aroundLine[aroundLineCount]=spheres[i];
        aroundLineCount++;
      }
    }

    for(i=0;i<aroundLineCount;i++){
      for(j=0;(j<aroundLineCount && j<15);j++){ //already ordered
        if(i!=j){
          d1=calculateDistance(aroundLine[i],aroundLine[j]);
          if(d1<result){
            result=d1;
          }
        }
      }
    }
    return result;
}
