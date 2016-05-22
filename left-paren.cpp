#include "left-paren.hpp"

std::string LeftParen::sign() {
  return "(";
}

int LeftParen::associativity() {
  return assoc::NONE;
}

int LeftParen::precedence() {
  return 0;
}
