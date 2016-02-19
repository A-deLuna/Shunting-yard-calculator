#include "shunting-yard.hpp"
#include <iostream>
#include <cassert>
int main() {
  assert(parse("5 + 3") == 8);
  std::cout<<"assertion passed '5 + 3' = 8"<<std::endl;
  assert(parse("5 + 3 + 6") == 14);
  std::cout<<"assertion passed '5 + 3 + 6' = 14"<<std::endl;
  assert(parse("5 - 3") == 2);
  std::cout<<"assertion passed '5 - 3' = 2"<<std::endl;
  assert(parse("5 - 3 - 1") == 1);
  std::cout<<"assertion passed '5 - 3 - 1' = 1"<<std::endl;
  assert(parse("5 + 3 - 1") == 7);
  std::cout<<"assertion passed '5 + 3 - 1' = 7"<<std::endl;
  assert(parse("5 * 3") == 15);
  std::cout<<"assertion passed '5 * 3' = 15"<<std::endl;
  assert(parse("5 * 3 * 2") == 30);
  std::cout<<"assertion passed '5 * 3 * 2' = 30"<<std::endl;
  assert(parse("5 - 3 * 2") == -1);
  std::cout<<"assertion passed '5 - 3 * 2' = -1"<<std::endl;
  assert(parse("4 / 2") == 2);
  std::cout<<"assertion passed '4 / 2' = 2"<<std::endl;
  assert(parse("3 / 2") == 1);
  std::cout<<"assertion passed '3 / 2' = 1"<<std::endl;
  assert(parse("4 + 4 / 2") == 6);
  std::cout<<"assertion passed '4 + 4 / 2' = 6"<<std::endl;
}
