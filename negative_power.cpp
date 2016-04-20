#include "negative_power.hpp"

Number NegativePower::eval(Number a, Number b) {
  Number ans;
  if(b < Number("0","0")) {
    return (Number::abs(b) ^ a) * Number("-1","0");
  }
  return (b ^ a);
}

int NegativePower::precedence() {
  return 9;
}

int NegativePower::associativity() {
  return assoc::RIGHT;
}

int NegativePower::arity() {
  return 2;
}

char NegativePower::sign() {
  return '^';
}
