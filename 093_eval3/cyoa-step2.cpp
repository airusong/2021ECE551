#include "page.h"
#include "story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage for step2 story" << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<page> pages = readStory(argv[1]);
  bool result = checkpages(pages);
  if (result == false) {
    std::cout << " page problem" << std::endl;
  }
  printStory(pages);
  //deletePages(pages);
  return EXIT_SUCCESS;
}
