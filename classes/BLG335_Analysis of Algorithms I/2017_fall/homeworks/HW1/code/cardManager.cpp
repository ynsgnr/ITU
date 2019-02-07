#ifdef DEBUG
#define DEBUGMODE(code) code
#else
#define DEBUGMODE(code)
#endif

#ifndef CARDMANAGER_CPP
#define CARDMANAGER_CPP


#include "cardManager.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>

const std::string cardManager::card::toString() const{
    return
      name + "\t" +
      cardClass + "\t" +
      rarity + "\t" +
      set + "\t" +
      type + "\t" +
      std::to_string(cost) + "\n";
 	}


const std::vector <std::string> cardManager::card::toStringVector() const{
    std::vector <std::string> data;
    data.resize(6);
    data[0]=name;
    data[1]=cardClass;
    data[2]=rarity;
    data[3]=set;
    data[4]=type;
    data[5]=std::to_string(cost);
    return data;
 	}

  cardManager::cardManager(){

 	}

  cardManager::cardManager(std::vector< std::vector<std::string> > data){
    setData(data);
 	}

  const std::vector< std::vector<std::string> > cardManager::getData() const {
    std::vector< std::vector<std::string> > data;
    int row;
    row=cards.size();
    data.resize(row);
    for(int r=0;r<row;r++){
      data[r]=cards[r].toStringVector();
    }

    return data;
 	}

  void cardManager::setData(std::vector< std::vector<std::string> > data){
      int column,row;
      card tmp;

      row=data.size();
      if(row<=0) throw "invalid data send to card manager";
      column=data[0].size();
      if(column>6) throw "invalid data send to card manager";

      cards.clear();
      cards.resize(row);

      DEBUGMODE(std::cout << "Memory allocated row:"<<row<<" column: "<<column << '\n';)

      for(int r=0;r<row;r++){
          cards[r].name=data[r][0];
          cards[r].cardClass=data[r][1];
          cards[r].rarity=data[r][2];
          cards[r].set=data[r][3];
          cards[r].type=data[r][4];
          cards[r].cost=atoi(data[r][5].c_str());
      }
 	}

  void cardManager::fullSort(char choosen){
    DEBUGMODE(std::cout << "start full sort" << '\n';)
    if (choosen=='i')
      fullInsertionSort();
    else if (choosen=='m'){
      data=getData(); //copied vector
      mergeSort(0,data.size()-1,1);//sorted by class
      std::string tmp=data[0][1];
      int start=0;
      int end=0;
      DEBUGMODE(
        std::cout << "Sorted Cards by class:" << '\n';
      )
      for(int i=0;i<data.size();i++){
        if (data[i][1]==tmp){
          end++;
        }else{
          DEBUGMODE(std::cout << "Changing class: " << tmp <<"-"<<end << '\n';)
          tmp=data[i][1];
          mergeSort(start,end-1,5);//sorted by cost
          start=end;
        }
      }
      DEBUGMODE(
        std::cout << "Sorted Cards by cost:" << '\n';
      )
      start=0;
      end=0;
      tmp=data[0][5];
      for(int i=0;i<data.size();i++){
        if (data[i][5]==tmp){
          end++;
        }else{
          tmp=data[i][5];
          mergeSort(start,end-1,0);//sorted by name
          start=end;
        }
      }
      DEBUGMODE(
        std::cout << "Sorted Cards:" << '\n';
      )
      setData(data);
    }else
      throw "Invalid input";
 	}

  void cardManager::filterSort(char choosen){
    if (choosen=='i')
      filterInsertionSort();
    else if (choosen=='m'){
      DEBUGMODE(std::cout << "Start filter merge sort" << '\n';)
      data=getData(); //copied vector
      DEBUGMODE(std::cout << "Vector copied" << '\n';)
      mergeSort(0,data.size()-1,4);
      setData(data);
      DEBUGMODE(
        std::cout << "Sorted Cards:" << '\n';
        for(int r=0;r<cards.size();r++){
          std::cout << cards[r].toString() << '\n';
        }
      )
    } else
      throw "Invalid input";
 	}

  void cardManager::mergeSort(int p, int r, int columnNo){
    if (p<r){
      int q=(p+r)/2;
      mergeSort(p,q,columnNo);
      mergeSort(q+1,r,columnNo);
      merge(p,q,r,columnNo);
    }
  }

  void cardManager::merge(int p, int q, int r, int columnNo){
    std::vector< std::vector<std::string> > tmp;
    int size=(r-p)+1;
    tmp.resize(size);
    int start=p;
    int middle=q+1;
    for (int i=0;i<size;i++){
      if(start>q){
        tmp[i]=data[middle];
        middle++;
      }else if(middle>r){
        tmp[i]=data[start];
        start++;
      }else{
        if(data[start][columnNo]<=data[middle][columnNo]){
          tmp[i]=data[start];
          start++;
        }else{
          tmp[i]=data[middle];
          middle++;
        }
      }
    }
    for(int i=0;i<size;i++){
      data[p+i]=tmp[i];
    }
  }

  void cardManager::fullInsertionSort(){
      DEBUGMODE(std::cout << "start full insertion sort" << '\n';)
      int i;
      card tmp;

      //sort by class
      for(int r=0;r<cards.size();r++){
        i=r;
        while(i>=1 && cards[i].cardClass<cards[i-1].cardClass){
          //switch
          tmp=cards[i];
          cards[i]=cards[i-1];
          cards[i-1]=tmp;
          i--;
        }
      }

      DEBUGMODE(
        std::cout << "Sorted Cards by class" << '\n';
      )

      //sort by cost
      for(int r=0;r<cards.size();r++){
        i=r;
        while( i>=1 && cards[i].cost<cards[i-1].cost
          && cards[i].cardClass==cards[i-1].cardClass/*sort only same classes*/){
          //switch
          tmp=cards[i];
          cards[i]=cards[i-1];
          cards[i-1]=tmp;
          i--;
        }
      }

      DEBUGMODE(
        std::cout << "Sorted Cards by cost" << '\n';
      )

      //sort by name
      for(int r=0;r<cards.size();r++){
        i=r;
        while( i>=1 && cards[i].name<cards[i-1].name
          && cards[i].cost==cards[i-1].cost/*sort only same costs*/){
          //switch
          tmp=cards[i];
          cards[i]=cards[i-1];
          cards[i-1]=tmp;
          i--;
        }
      }
      DEBUGMODE(
        std::cout << "Sorted Cards by name" << '\n';
      )
 	}

  void cardManager::filterInsertionSort(){
    DEBUGMODE(std::cout << "start filter insertion sort" << '\n';)
    int i;
    card tmp;

    //sort by type
    for(int r=0;r<cards.size();r++){
      i=r;
      while(i>=1 && cards[i].type<cards[i-1].type){
        //switch
        tmp=cards[i];
        cards[i]=cards[i-1];
        cards[i-1]=tmp;
        i--;
      }
    }
  }

  const std::vector<std::string> cardManager::operator[](int i) const{
    std::vector<std::string> data;
    data=cards[i].toStringVector();
    return data;
  };

  int cardManager::size(){
    return cards.size();
  }

#endif
