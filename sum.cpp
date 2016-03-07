#include "sum.hpp"
#include <string>

long long Sum::eval(long long a, long long b) {
  long long ans = a + b;
  if(ans > MAX_NUM) {
    throw std::string("Integer Overflow");
  }
  if(ans < MIN_NUM) {
    throw std::string("Integer Underflow");
  }
  return ans;
}

int Sum::precedence() {
  return 2;
}

int Sum::associativity() {
  return assoc::LEFT;
}

int Sum::arity() {
  return 2;
}

char Sum::sign() {
  return '+';
}
