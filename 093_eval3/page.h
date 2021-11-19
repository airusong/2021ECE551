#ifndef __T_PAGE_H___
#define __T_PAGE_H___
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class myexception : public std::exception {
 public:
  const char * what() const throw() { return "no # seperate"; }
};
class page {
 public:
  int pageNum;
  bool visited;
  int dist;
  page * prev;
  std::vector<std::string> choice;
  std::string result;
  std::vector<std::string> text;

  std::vector<int> choiceNum;
  int choiceSize;
  page(std::ifstream & f, int number) :
      pageNum(number),
      visited(false),
      dist(INT_MAX),
      prev(NULL) {
    std::string line;
    std::string newLine;
    std::string str1("WIN");
    std::string str2("LOSE");
    int flag = 0;
    int pos1 = 0;
    int num = 0;
    int choiceSize = 0;
    //    dist = INT_MAX;
    while (getline(f, line)) {
      if (line[0] == '#') {
        // line.clear();
        break;
      }
      if (line.compare(str1) == 0) {
        result = str1;
        //line.clear();
        break;
      }
      else if (line.compare(str2) == 0) {
        result = str2;
        // line.clear();
        break;
      }
      else {
        choice.push_back(line);
        pos1 = line.find(":");
        num = atoi(line.substr(0, pos1).c_str());
        choiceNum.push_back(num);
        choiceSize++;
      }
    }
    std::string line2;
    while (getline(f, line2)) {
      if (flag == 0 && line2[0] != '#') {
        text.push_back(line2);
        line2.clear();
        //  continue;
      }

      // flag = 1;
      //  std::cout << line2 << std::endl;
      //  line2.clear();
      //  continue;
      // }
      //if (flag == 1) {
      // text.push_back(line2);

      // std::cout << line2 << std::endl;
      // }
    }
  }
  int getChoiceSize() { return choiceNum.size(); }
  int getDistance() { return dist; }
  void setDistance(int distance) { this->dist = distance; }
  page & operator=(const page & rhs) {
    if (this != &rhs) {
      this->pageNum = rhs.pageNum;
      this->visited = rhs.visited;
      this->dist = rhs.dist;
      this->result = rhs.result;
      this->choiceSize = rhs.choiceSize;
      for (size_t i = 0; i < rhs.choice.size(); i++) {
        this->choice.push_back(rhs.choice[i]);
      }
      for (size_t i = 0; i < rhs.text.size(); i++) {
        this->text.push_back(rhs.text[i]);
      }
      for (size_t i = 0; i < rhs.choiceNum.size(); i++) {
        this->choiceNum.push_back(rhs.choiceNum[i]);
      }
    }
    return *this;
  }
};
void printFile(page ans) {
  std::vector<std::string>::iterator it = ans.text.begin();
  while (it != ans.text.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
  std::cout << std::endl;
  int count = 1;
  int pos;
  std::string temp;
  if (ans.result.compare("WIN") == 0) {
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else if (ans.result.compare("LOSE") == 0) {
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
  else {
    std::cout << "What would you like to do?"
              << "\n"
              << std::endl;
    std::vector<std::string>::iterator it2 = ans.choice.begin();
    while (it2 != ans.choice.end()) {
      temp = *it2;
      pos = temp.find(":");
      temp = temp.substr(pos + 1);
      std::cout << " " << count << "."
                << " " << temp << "\n";
      count++;
      ++it2;
      temp.clear();
      pos = 0;
    }
  }
}
#endif
