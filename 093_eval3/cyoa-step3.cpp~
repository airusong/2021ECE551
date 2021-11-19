#include "page.h"
#include "story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage for step3 story" << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<page> pages = readStory(argv[1]);
  bool result = checkpages(pages);
  if (result == false) {
    std::cout << " page problem" << std::endl;
  }
  findPath(pages);
  printpageDepth(pages);
  return EXIT_SUCCESS;
}
