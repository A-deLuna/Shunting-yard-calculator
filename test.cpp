#ifdef TEST
#include "shunting-yard.hpp"
#include <iostream>
#include <cassert>

void test_exception(const std::string& operation, const std::string& exception);
void test_answer(const std::string& operation, int exception);


void run() {
  test_answer("5=" , 5);
  test_answer("5+3=" , 8);
  test_answer("5+3+6 =" , 14);
  test_answer("5-3 =", 2);
  test_answer("5-3 -    1 =", 1);
  test_answer("5+3 - 1 =", 7);
  test_answer("5*3=", 15);
  test_answer("5 * 3 * 2=", 30);
  test_answer("5 - 3 *2=", -1);
  test_answer("4 / 2 =", 2);
  test_answer("3 /2=", 1);
  test_answer("4 + 4 / 2 =", 6);
  test_answer("-5=", -5);
  test_answer("5 - -3=", 8);
  test_answer("5 + - 3 =", 2);
  test_answer("5 * -3=", -15);
  test_answer("(5)=", 5);
  test_answer("(5 + 3)=", 8);
  test_answer("(5 + 3) / 2=", 4);
  test_answer("(6 + (11-2) * 2) / 2=", 12);

  test_exception("+=", "Too few operands");
  test_exception("5++ 3 =", "Too few operands");
  test_exception("5 -+3 =", "Too few operands");
  test_exception("5 - --3 =", "Too few operands");
  test_exception("5 /0 =", "Division by zero");
  test_exception("1000000000000 =", "Integer Overflow");
  test_exception("999999999999 + 1 =", "Integer Overflow");
  test_exception("999999999999 * 2 =", "Integer Overflow");
  test_exception("5 5+ 3 =", "Too many operands");
  test_exception("5 + 3", "Missing =");
  test_exception("a=", "Unexpected Token 'a'");
  test_exception("5a=", "Unexpected Token '5a'");
  // test_exception("5/(a)=", "Unexpected Token '('");
  test_exception("999999999999 * 999999999999=", "Integer Overflow");
  test_exception("(55=", "mismatched parens");
  test_exception("55)=", "mismatched parens");
}

int main(int argc, char **argv) {
  if(argc == 1) {
    try {
      run();
    }
    catch(const std::string & msg) {
      std::cout <<"Test_answer raised exception "<< msg << std::endl;
    }
  }
  else if(argc == 2) {
    std::vector<std::string> v;
    try {
      std::cout<<argv[1] << " "<< parse(argv[1], v)<<std::endl;
      for(auto s : v) {
        std::cout<< s <<"\n";
      }
    }
    catch(const std::string & msg) {
      std::cout<< "Raised exception "<< msg << std::endl;
    }
  }
}

void test_answer(const std::string & operation, int result) {
  std::vector<std::string> v;
  Number n (result, 1);
  assert(parse(operation, v) == n);
  std::cout<<"assertion passed '"<< operation <<"' = " << result<<std::endl;
}

void test_exception (const std::string & operation, const std::string & exception) {
  std::string test = "";
  std::vector<std::string> v;
  try {
    parse(operation, v);
  }
  catch (std::string & msg){
    test = msg;
  }
  assert(test == exception);
  std::cout<<"assertion passed '"<< operation <<"' = " << exception <<std::endl;

}
#endif
