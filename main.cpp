#include "shunting-yard.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

void test_exception (const char* operation, const char* exception) {
  const char * test = "";
  try {
    parse(operation);
  }
  catch (const char* msg){
    test = msg;
  }
  assert(strcmp(test, exception) == 0);
  std::cout<<"assertion passed '"<< operation <<"' = " << exception <<std::endl;

}

int main() {
  assert(parse("5 + 3") == 8); std::cout<<"assertion passed '5 + 3' = 8"<<std::endl;
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

  test_exception("+", "Too few operands");
  test_exception("5 + + 3", "Too few operands");
  test_exception("1000000000000", "Integer Overflow");
  test_exception("999999999999 + 1", "Integer Overflow");
  test_exception("999999999999 * 2", "Integer Overflow");
}
