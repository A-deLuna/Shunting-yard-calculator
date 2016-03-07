#include "substraction.hpp"
#include <string>
long long Substraction::eval(long long a, long long b) {

    long long ans = b - a;
    if(ans > MAX_NUM) {
      throw std::string("Integer Overflow");
    }
    if(ans < MIN_NUM) {
      throw std::string("Integer Underflow");
    }
    return ans;
}

int Substraction::precedence() {
    return 2;
}

int Substraction::associativity() {
    return assoc::LEFT;
}

int Substraction::arity() {
  return 2;
}
char Substraction::sign() {
  return '-';
}
