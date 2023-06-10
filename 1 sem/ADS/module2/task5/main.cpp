#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main() {
  // if (system("g++ bebra.cpp -o outputfile.exe")){
  //   std::cout<<"OK"<<std::endl;
  // } else {
  //   std::cout<<"FAIL"<<std::endl;
  // }

  std::string line;

  std::ifstream in("./huy.cpp");  // окрываем файл для чтения
  if (in.is_open()) {
    while (std::getline(in, line)) {
      std::cout << line << std::endl;
    }
  }
}