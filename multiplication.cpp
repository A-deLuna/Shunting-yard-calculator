#include "multiplication.hpp"

long long Multiplication::eval(long long a, long long b) {
  long long ans = a * b;
  if(ans > MAX_NUM) {
    throw "Integer Overflow";
  }
  return ans;
}

int Multiplication::precedence() {
  return 3;
}

int Multiplication::associativity() {
  return assoc::LEFT;
}
