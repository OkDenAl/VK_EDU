#include <fstream>
#include <iostream>

#include "MathParser.h"
#include "AstNode.h"

void printUsageForm() {
  std::cout << "Usage: ./calculator '<Expression>'\n"
               "Supported opperations: '+', '-', '*', 'sin', 'ln'. Also '(' "
               "and ')' supported !\n"
               "Please make sense about correct brackets !"
            << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Argument count is invalid" << std::endl;
    printUsageForm();
    return 1;
  }

  std::string inputLine = static_cast<std::string>(argv[argc - 1]);

  try {
    auto syntaxTree = MathParser(inputLine).Parse();
    double res = syntaxTree->GetData()->Calculate();
    std::cout << res << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl << std::endl;
    printUsageForm();
  }
}
