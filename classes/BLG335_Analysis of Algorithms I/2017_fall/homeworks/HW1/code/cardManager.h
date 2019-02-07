#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <string>

/* @Author
* Student Name: Yunus Güngör
* Student ID : 150150701
*/

class cardManager{
public:
  cardManager();
  cardManager(std::vector< std::vector<std::string> >);
  int size();
  const std::vector< std::vector<std::string> > getData() const;
  void setData(std::vector< std::vector<std::string> >);
  void fullSort(char);
  void filterSort(char);
  const std::vector<std::string> operator[](int) const;
private:
  class card{
    public:
        const std::string toString() const;
        const std::vector <std::string> toStringVector() const;
        std::string name;
        std::string cardClass;
        std::string rarity;
        std::string set;
        std::string type;
        int cost;
  };
  std::vector< std::vector<std::string> > data;
  void fullInsertionSort();
  void filterInsertionSort();
  void mergeSort(int, int, int);
  void merge(int, int, int, int);
  std::vector<card> cards;
};

#include "cardManager.cpp"

#endif // CARDMANAGER_H
