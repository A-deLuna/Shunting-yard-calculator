#ifdef TEST
#include "shunting-yard.hpp"
#include <iostream>
#include <cassert>

void test_exception(const std::string& operation, const std::string& exception);
void test_answer(const std::string& operation, const std::string& ans);


void run() {
  test_answer("5=" ,"5");
  test_answer("5+3=" , "8");
  test_answer("5+3+6 =" , "14");
  test_answer("5-3 =", "2");
  test_answer("5-3 -    1 =", "1");
  test_answer("5+3 - 1 =", "7");
  test_answer("5*3=", "15");
  test_answer("5 * 3 * 2=", "30");
  test_answer("5 - 3 *2=", " -1");
  test_answer("4 / 2 =", "2");
  test_answer("3 /2=", "1.5");
  test_answer("4 + 4 / 2 =", "6");
  test_answer("-5=", "-5");
  test_answer("5 - -3=", "8");
  test_answer("5 + - 3 =", "2");
  test_answer("5 * -3=", "-15");
  test_answer("(5)=", "5");
  test_answer("(5 + 3)=", "8");
  test_answer("(5 + 3) / 2=", "4");
  test_answer("(5 + (11-2) * 2) / 2=", "11.5");
  test_answer("5.3 + 8.2 * 2.1 =", "22.52");
  //TODO: fix this case
  //test_answer("4.75--8.43*--1.01=", "13.2643");
  test_answer("(3.2-((4.2+8.1)*2)-1)=", "-22.4");
  test_answer("1E1 - 2E-2=", "9.98");
  test_answer("5--2E-2=", "5.02");
  //test_answer("4 + 3E", "");
  //test_answer("A * 2", "");
  //test_answer("6.5 - 2.5/2 = A", "");
  //test_answer(*2.5 = "B", "");
  //test_answer("A + B = C", "");
  //test_answer("C =", "");
  test_answer("12345678 * 100=", "1234567800");
  test_answer("999999999+3=", "1000000002");
  test_answer("99999*99999*2000=", "1.99996E13");
  test_answer("0.33333333- 1/3=", "0");
  test_answer("3/5 - 0.59999999 =", "0.0000001");
  // TODO: CHECK THIS ONE LATER
  test_answer("1/2*2.0000001=", "1.0000001");
//  test_answer("1-(-4)^(1/2)=", "");
//  test_answer("(1-1)/2=", "");
//  test_answer("2/(1-1)=", "");
//  test_answer("4^-5=", "");
//  test_answer("1 + 1* 1/1=", "");
  
  test_exception("+=", "Too few operands");
  test_exception("5++ 3 =", "Too few operands");
  test_exception("5 -+3 =", "Too few operands");
  test_exception("5 - --3 =", "Too few operands");
  test_exception("5 /0 =", "Division by zero");
//  test_exception("1000000000000 =", "Integer Overflow");
//  test_exception("999999999999 + 1 =", "Integer Overflow");
//  test_exception("999999999999 * 2 =", "Integer Overflow");
  test_exception("5 5+ 3 =", "Too many operands");
  test_exception("5 + 3", "Missing =");
  test_exception("a=", "Unexpected Token 'a'");
  test_exception("5a=", "Unexpected Token '5a'");
  // test_exception("5/(a)=", "Unexpected Token '('");
  // test_exception("999999999999 * 999999999999=", "Integer Overflow");
  test_exception("(55=", "mismatched parens");
  test_exception("55)=", "mismatched parens");
   test_exception("(3-(2+((4*2.1)-1)=", "mismatched parens");
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
  else if(argc == 3) {
    test_answer(argv[1], argv[2]);
  }
}

void test_answer(const std::string& operation, const std::string& result) {
  std::vector<std::string> v;
  Number n (result, "0");
  Number t = parse(operation, v); 
  std::cout << "string operation '" << operation << "',  result as stream: " << t <<
         ", string expected res: " << result << ", expected res parsed as: " << n << "\n";
  std::cout<< t.mantissa << ": E" <<t.exponent << "\n"; 
  assert(t == n);
  std::cout<<" assertion passed   " <<std::endl;
}

void test_exception(const std::string & operation, const std::string& exception) {
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
