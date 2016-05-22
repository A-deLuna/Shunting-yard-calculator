#include "root.hpp"

Number Root::eval(Number a, Number b) {
  return Number::nthRoot(a, b) ; 
}

std::string Root::sign() {
  return "r";
}

int Root::associativity() {
  return assoc::NONE;
}

int Root::precedence() {
  return 0;
}
