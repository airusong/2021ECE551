#include "page.h"
#include "story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage for step2 story" << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<page> pages = readStory(argv[1]);
  //  int pageNum = 12;
  winPath(pages);
  return EXIT_SUCCESS;
}
