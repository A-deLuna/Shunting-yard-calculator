#include "shunting-yard.hpp"
#include <iostream>
#include <cassert>
int main() {
  int ans;
  ans = parse("5 + 3");
  assert(ans == 8);
  std::cout<<"assertion passed '5 + 3' = 8"<<std::endl;
  ans = parse("5 + 3 + 6");
  assert(ans == 14);
  std::cout<<"assertion passed '5 + 3 + 6' = 14"<<std::endl;
  ans = parse("5 - 3");
  assert(ans == 2);
  std::cout<<"assertion passed '5 - 3' = 2"<<std::endl;
  ans = parse("5 - 3 - 1");
  assert(ans == 1);
  std::cout<<"assertion passed '5 - 3 - 1' = 1"<<std::endl;
  ans = parse("5 + 3 - 1");
  assert(ans == 7);
  std::cout<<"assertion passed '5 + 3 - 1' = 7"<<std::endl;
  ans = parse("5 * 3");
  assert(ans == 15);
  std::cout<<"assertion passed '5 * 3' = 15"<<std::endl;
  ans = parse("5 * 3 * 2");
  assert(ans == 30);
  std::cout<<"assertion passed '5 * 3 * 2' = 30"<<std::endl;
  ans = parse("5 - 3 * 2");
  assert(ans == -1);
  std::cout<<"assertion passed '5 - 3 * 2' = -1"<<std::endl;
}
