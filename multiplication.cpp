#include "multiplication.hpp"
#include <string>
Number Multiplication::eval(Number a, Number b) {
  Number ans = a * b;
  //if(ans > MAX_NUM) {
  //  throw std::string("Integer Overflow");
  //}
  //if(ans < MIN_NUM) {
  //  throw std::string("Integer Underflow");
  //}
  return ans;
}

int Multiplication::precedence() {
  return 3;
}

int Multiplication::associativity() {
  return assoc::LEFT;
}

int Multiplication::arity() {
    return 2;
}

char Multiplication::sign() {
  return '*';
}
