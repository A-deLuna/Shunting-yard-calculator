#include "power.hpp"

Number Power::eval(Number a, Number b) {
  return b ^ a;
}

int Power::precedence() {
  return 9;
}

int Power::associativity() {
  return assoc::RIGHT;
}

int Power::arity() {
  return 2;
}

std::string Power::sign() {
  return "^";
}
