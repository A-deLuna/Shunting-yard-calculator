#include "sum.hpp"

long long Sum::eval(long long a, long long b) {
  long long ans = a + b;
  if(ans > MAX_NUM) {
    throw "Integer Overflow";
  }
  return ans;
}

int Sum::precedence() {
  return 2;
}

int Sum::associativity() {
  return assoc::LEFT;
}
