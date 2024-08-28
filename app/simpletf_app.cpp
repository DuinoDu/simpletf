#include "simpletf/simpletf.hpp"
#include <iostream>

int main(){
  int result = simpletf::add_one(1);
  std::cout << "1 + 1 = " << result << std::endl;
}