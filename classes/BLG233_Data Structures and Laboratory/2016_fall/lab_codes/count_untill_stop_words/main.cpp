#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
*/

#define  SWFILE "stopwords.txt"
#define INPUTFILE "input.txt"


set<string> getStopWords();


int main(){

    int stopWordCount=0;


	set<string> stopWords;
	set<string>::iterator SWit;

	map<string,float> frequency;
	map<string,float>::iterator it;
	map<string,float>::iterator maxIt;

	string word;


	stopWords=getStopWords();
	//if(!stopWords) return 1;

	/*for(SWit=stopWords.begin();SWit!=stopWords.end();SWit++){
			cout<<*SWit<<endl;
		}*/

	ifstream inputFile (INPUTFILE);
      if (inputFile.is_open())
      {
		while (inputFile >> word)
		{
			if(stopWords.find(word)!=stopWords.end()){
				//calculate count
				stopWordCount++;
				frequency[word]++;
			}

		}
		inputFile.close();

		//print
		int j=frequency.size();
		for(int i=0;i<j;i++){
            it=frequency.begin();
            maxIt=frequency.begin();
            while(it!=frequency.end()){
                if(maxIt->second < it->second){
                    maxIt=it;
                }
                it++;
            }
            cout<<maxIt->first<<"-"<<(float)maxIt->second*100/(float)stopWordCount<<endl;
            frequency.erase(maxIt);
		}
      }

	return 0;
}

set<string> getStopWords(){

	string word;
	set<string> stopWords;

	ifstream swFile (SWFILE);
      if (swFile.is_open())
      {
		while (swFile >> word)
		{
		    stopWords.insert(word);
		}
		swFile.close();

      }
      else
        cout<<"Error opening file"<<endl;
      return stopWords;
}


