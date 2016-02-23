#include "shunting-yard.hpp"
#include <iostream>
#include <cassert>
#include <string>

void test_exception(const std::string& operation, const std::string& exception);
void test_answer(const std::string& operation, long long exception);


void run() {
  test_answer("5 =" , 5);
  test_answer("5 + 3 =" , 8);
  test_answer("5 + 3 + 6 =" , 14);
  test_answer("5 - 3 =", 2);
  test_answer("5 - 3 - 1 =", 1);
  test_answer("5 + 3 - 1 =", 7);
  test_answer("5 * 3 =", 15);
  test_answer("5 * 3 * 2 =", 30);
  test_answer("5 - 3 * 2 =", -1);
  test_answer("4 / 2 =", 2);
  test_answer("3 / 2 =", 1);
  test_answer("4 + 4 / 2 =", 6);
  test_answer("- 5 =", -5);
  test_answer("5 - - 3 =", 8);
  test_answer("5 + - 3 =", 2);
  test_answer("5 * - 3 =", -15);

  test_exception("+ =", "Too few operands");
  test_exception("5 + + 3 =", "Too few operands");
  test_exception("5 - + 3 =", "Too few operands");
  test_exception("5 - - - 3 =", "Too few operands");
  test_exception("5 / 0 =", "Division by zero");
  test_exception("1000000000000 =", "Integer Overflow");
  test_exception("999999999999 + 1 =", "Integer Overflow");
  test_exception("999999999999 * 2 =", "Integer Overflow");
  test_exception("5 5 + 3 =", "Too many operands");
  test_exception("5 + 3", "Missing =");
}
int main() {
  try {
    run();
  }
  catch(const std::string & msg) {
    std::cout <<"Test_answer raised exception "<< msg << std::endl;
  }
}

void test_answer(const std::string & operation, long long result) {
  assert(parse(operation) == result);
  std::cout<<"assertion passed '"<< operation <<"' = " << result<<std::endl;
}

void test_exception (const std::string & operation, const std::string & exception) {
  std::string test = "";
  try {
    parse(operation);
  }
  catch (std::string & msg){
    test = msg;
  }
  assert(test == exception);
  std::cout<<"assertion passed '"<< operation <<"' = " << exception <<std::endl;

}
