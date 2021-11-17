#include "page.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage for step1 page file" << std::endl;
    return EXIT_FAILURE;
  }

  std::ifstream pageFile;
  pageFile.open(argv[1]);
  if (!pageFile.good()) {
    std::cerr << "Can not open file " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }
  //int pageNum = 0;
  page * ans = new page(pageFile, 0);
  printFile(ans);
  pageFile.close();
  delete ans;
  return EXIT_SUCCESS;
}
