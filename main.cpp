#include "shunting-yard.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

void test_exception(const char* operation, const char* exception);
void test_answer(const char* operation, long long exception);


void run() {
  test_answer("5" , 5);
  test_answer("5 + 3" , 8);
  test_answer("5 + 3 + 6" , 14);
  test_answer("5 - 3", 2);
  test_answer("5 - 3 - 1", 1);
  test_answer("5 + 3 - 1", 7);
  test_answer("5 * 3", 15);
  test_answer("5 * 3 * 2", 30);
  test_answer("5 - 3 * 2", -1);
  test_answer("4 / 2", 2);
  test_answer("3 / 2", 1);
  test_answer("4 + 4 / 2", 6);

  test_exception("+", "Too few operands");
  test_exception("5 + + 3", "Too few operands");
  test_exception("1000000000000", "Integer Overflow");
  test_exception("999999999999 + 1", "Integer Overflow");
  test_exception("999999999999 * 2", "Integer Overflow");
  test_exception("5 5 + 3", "Too many operands");
}
int main() {
  try {
    run();
  }
  catch(const char* msg) {
    std::cout << msg << std::endl;
  }
}

void test_answer(const char* operation, long long result) {
  assert(parse(operation) == result);
  std::cout<<"assertion passed '"<< operation <<"' = " << result<<std::endl;
}

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
