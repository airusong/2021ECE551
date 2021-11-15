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
  std::string pagename = getPname(pageNum, directory);
  std::ifstream pagefile;
  pagefile.open(pagename);
  page * currpage = new page(pagefile);
}
#endif
