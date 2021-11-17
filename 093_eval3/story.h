#ifndef _STORY_H__
#define _STORY_H__
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "page.h"
//step2
int getInputNum(int size) {
  //std::string line;
  int inputNum = 0;
  while (true) {
    std::cin >> inputNum;
    //getline(std::cin, line);
    //const char * number = line.c_str();
    //inputNum = atoi(number);
    if (inputNum <= 0 || inputNum > size) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }
    else {
      break;
    }
  }
  return inputNum;
}
std::string getPname(int & pageNum, const char * directory) {
  std::string pagename;
  std::string str1(directory);
  std::string str2("/page");
  std::string str3(std::to_string(pageNum));
  std::string str4(".txt");
  pagename = str1 + str2 + str3 + str4;
  return pagename;
}
std::vector<page *> readStory(char * directory) {
  std::vector<page *> pages;
  int pageNum = 1;
  //check if page1.txt exist
  std::ifstream first;
  std::string pagestring = getPname(pageNum, directory);
  const char * pagename = pagestring.c_str();
  first.open(pagename);
  if (!first.good()) {
    std::cerr << "page1.txt do not exist in the story" << std::endl;
    exit(EXIT_FAILURE);
  }
  first.close();
  //read from page1 until story end and store all pages into the vector
  while (true) {
    std::string pageNamestring = getPname(pageNum, directory);
    const char * pageName = pageNamestring.c_str();
    std::ifstream pagefile;
    pagefile.open(pageName);
    if (!pagefile.good()) {
      //  std::cout << "page " << pageNum - 1 << "end" << std::endl;
      break;
    }
    page * currpage = new page(pagefile, pageNum);
    pages.push_back(currpage);
    pagefile.close();
    pageNum++;
  }
  return pages;
}
bool checkpages(std::vector<page *> & pages) {
  int pageAmount = pages.size();
  std::vector<page *>::iterator it = pages.begin();
  std::set<int> referPage;
  bool result = true;
  //make sure every page that is referenced by a choice is valid
  while (it != pages.end()) {
    int size = (*it)->getChoiceSize();
    for (int j = 0; j < size; j++) {
      if ((*it)->choiceNum[j] > pageAmount || (*it)->choiceNum[j] <= 0) {
        std::cerr << "page that is referenced by a choice is invalid" << std::endl;
        result = false;
      }
      else {
        if (referPage.count(((*it)->choiceNum[j])) == 0) {
          referPage.insert(((*it)->choiceNum[j]));
          //  std::cout << (*it)->choiceNum[j] << std::endl;
        }
      }
    }
    ++it;
  }
  //Every page (except page 1) is referenced by at least one other choice
  for (int j = 2; j <= pageAmount; j++) {
    if (referPage.count(j) == 0) {
      std::cerr << "page" << j << "is not referenced by another page" << std::endl;
      result = false;
    }
  }
  //at least one page must be a WIN page and at least one page must be a LOSE page.
  it = pages.begin();
  int winFlag = 0;
  int loseFlag = 0;
  while (it != pages.end()) {
    if ((*it)->result == "WIN") {
      winFlag = 1;
    }
    if ((*it)->result == "LOSE") {
      loseFlag = 1;
    }
    ++it;
  }
  if (winFlag == 0 || loseFlag == 0) {
    std::cerr << "lack win or lose page" << std::endl;
    result = false;
  }
  return result;
}
void printStory(std::vector<page *> & pages) {
  int pageNumber = 1;
  int pageChoice = 0;
  while (true) {
    printFile(pages[pageNumber - 1]);
    if (pages[pageNumber - 1]->result == "WIN" ||
        pages[pageNumber - 1]->result == "LOSE") {
      break;
    }
    //get the number user put in
    pageChoice = getInputNum(pages[pageNumber - 1]->getChoiceSize());
    pageNumber = pages[pageNumber - 1]->choiceNum[pageChoice - 1];
  }
}
void deletePages(std::vector<page *> & pages) {
  std::vector<page *>::iterator it = pages.begin();
  int size = pages.size();
  for (int i = 0; i < size; i++) {
    delete *it;
    ++it;
  }
}
#endif
