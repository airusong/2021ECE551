#ifndef _STORY_H__
#define _STORY_H__
#include <set>
#include <stack>
#include <string>

#include "page.h"
//step2
std::string getPname(int pageNum, const char * directory) {
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
  while (true) {
    std::string pagename = getPname(pageNum, directory);
    std::ifstream pagefile;
    pagefile.open(pagename);
    if (!pagefile.good()) {
      std::cerr << "Can not open file,story end " << pagename << std::endl;
      break;
    }
    page * currpage = new page(pagefile, pageNum);
    pages.push_back(currpage);
    pageNum++;
  }
  return pages;
}
bool checkpages(std::vector<page *> pages) {
  int pageAmount = pages.size();
  std::vector<page *>::iterator it = pages.begin();
  std::set<int> referPage;
  //make sure every page that is referenced by a choice is valid
  while (it != pages.end()) {
    int size = ((*it)->choiceNum).size();
    for (int i = 0; i < size; i++) {
      if ((*it)->choiceNum[i] > pageAmount || (*it)->choiceNum[i] <= 0) {
        std::cerr << "page that is referenced by a choice is invalid" << std::endl;
        return false;
      }
      else {
        if (referPage.count(((*it)->choiceNum[i])) == 0) {
          referPage.insert(((*it)->choiceNum[i]));
        }
      }
    }
    ++it;
  }
  //Every page (except page 1) is referenced by at least one other choice
  for (int j = 2; j <= pageAmount; j++) {
    if (referPage.count(j) == 0) {
      std::cerr << "page" << j << "is not referenced by another page" << std::endl;
      return false;
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
    return false;
  }
  return true;
}
#endif
