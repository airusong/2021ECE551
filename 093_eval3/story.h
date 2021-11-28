#ifndef _STORY_H__
#define _STORY_H__
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "page.h"
//step2
//get the choice number user input
int getInputNum(int size) {
  int inputNum = 0;
  while (true) {
    std::cin >> inputNum;
    if (inputNum <= 0 || inputNum > size) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }
    else {
      break;
    }
  }
  return inputNum;
}
//get the pagename
std::string getPname(int & pageNum, const char * directory) {
  std::string pagename;
  std::string str1(directory);
  std::string str2("/page");
  std::string str3(std::to_string(pageNum));
  std::string str4(".txt");
  pagename = str1 + str2 + str3 + str4;
  return pagename;
}
//read each page of the story
std::vector<page> readStory(char * directory) {
  std::vector<page> pages;
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
  //read from page1 until story end and store all pages into the vector page
  while (true) {
    std::string pageNamestring = getPname(pageNum, directory);
    const char * pageName = pageNamestring.c_str();
    std::ifstream pagefile;
    pagefile.open(pageName);
    if (!pagefile.good()) {
      break;
    }
    page currpage(pagefile, pageNum);
    pages.push_back(currpage);
    pagefile.close();
    pageNum++;
  }
  return pages;
}
//check if all the pages are valid
bool checkpages(std::vector<page> & pages) {
  int pageAmount = pages.size();
  std::vector<page>::iterator it = pages.begin();
  std::set<int> referPage;
  bool result = true;
  //make sure every page that is referenced by a choice is valid
  while (it != pages.end()) {
    int size = (*it).getChoiceSize();
    for (int j = 0; j < size; j++) {
      if ((*it).choiceNum[j] > pageAmount || (*it).choiceNum[j] <= 0) {
        std::cerr << "page that is referenced by a choice is invalid" << std::endl;
        result = false;
      }
      else {
        if (referPage.count(((*it).choiceNum[j])) == 0) {
          referPage.insert(((*it).choiceNum[j]));
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
    if ((*it).result == "WIN") {
      winFlag = 1;
    }
    if ((*it).result == "LOSE") {
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
//print story
void printStory(std::vector<page> & pages) {
  int pageNumber = 1;
  int pageChoice = 0;
  while (true) {
    printFile(pages[pageNumber - 1]);
    if (pages[pageNumber - 1].result == "WIN" || pages[pageNumber - 1].result == "LOSE") {
      break;
    }
    //get the number user put in
    pageChoice = getInputNum(pages[pageNumber - 1].getChoiceSize());
    pageNumber = pages[pageNumber - 1].choiceNum[pageChoice - 1];
  }
}
//step3
//using a BFS to find the depth of the pages
void findPath(std::vector<page> & pages) {
  std::queue<page> adjList;
  pages[0].setDistance(0);  //change the dist of page1 to 0
  pages[0].visited = true;  // change the visited of page1 to true
  adjList.push(pages[0]);   //push page1 into stack
  //page currpage = pages[0];
  while (!adjList.empty()) {
    page currpage = adjList.front();
    adjList.pop();
    //return the top of the page in stack;
    int distance = currpage.dist;
    if (currpage.result == "WIN" || currpage.result == "LOSE") {
      //find the exit of the story
      continue;
    }
    for (int i = 0; i < currpage.getChoiceSize(); i++) {
      if (pages[currpage.choiceNum[i] - 1].visited == false) {
        pages[currpage.choiceNum[i] - 1].visited = true;
        pages[currpage.choiceNum[i] - 1].prev = &currpage;
        pages[currpage.choiceNum[i] - 1].setDistance(distance + 1);
        adjList.push(pages[currpage.choiceNum[i] - 1]);
      }
    }
  }
}
void printpageDepth(std::vector<page> & pages) {
  std::vector<page>::iterator it = pages.begin();
  while (it != pages.end()) {
    if ((*it).visited == true) {
      std::cout << "Page " << (*it).pageNum << ":" << (*it).dist << std::endl;
    }
    else {
      std::cout << "Page " << (*it).pageNum << " "
                << "is not reachable" << std::endl;
    }
    ++it;
  }
}
//step4
void tracePath(std::vector<page> & pages,
               page & startpage,
               std::vector<int> pagepath,
               std::vector<page> path,
               std::vector<std::vector<page> > & result) {
  page currpage = startpage;
  //make sure there is no cycle in the path
  if ((std::find(pagepath.begin(), pagepath.end(), currpage.pageNum)) != pagepath.end()) {
    return;
  }
  path.push_back(currpage);
  pagepath.push_back(currpage.pageNum);
  if (currpage.result == "WIN") {
    result.push_back(path);
    return;
  }
  //DFS, go down the path until found the win page,then go down another path in the same way.
  for (int i = 0; i < currpage.getChoiceSize(); i++) {
    tracePath(pages, pages[currpage.choiceNum[i] - 1], pagepath, path, result);
  }
}
//make sure the choice of the current page by the pageNumber of the nextpage
int findChoice(page & page, int & nextpage) {
  int i = 0;
  int choice = 0;
  for (i = 0; i < page.getChoiceSize(); i++) {
    if (nextpage == page.choiceNum[i]) {
      choice = i + 1;
      break;
    }
  }
  return choice;
}
//store each win path in vector path and store all the path in vector result
//print them by traverse the vector in a for loop
void winPath(std::vector<page> & pages) {
  std::vector<page> path;
  std::vector<std::vector<page> > result;
  std::vector<int> pagepath;  //store the pageNumber that has been visited
  tracePath(pages, pages[0], pagepath, path, result);
  std::vector<std::vector<page> >::iterator it = result.begin();
  while (it != result.end()) {
    std::vector<page>::iterator it2 = (*it).begin();
    while (it2 != (*it).end()) {
      if (it2 != (*it).end() - 1) {
        int pagenum = (*it2).pageNum;
        page currpage = *it2;
        ++it2;
        std::cout << pagenum << "(" << findChoice(currpage, (*(it2)).pageNum) << "),";
      }
      else {
        std::cout << (*it2).pageNum << "(win)";
        ++it2;
      }
    }
    std::cout << std::endl;
    ++it;
  }
}

#endif
