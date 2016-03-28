#include "left-paren.hpp"

char LeftParen::sign() {
  return '(';
}

int LeftParen::associativity() {
  return assoc::NONE;
}

int LeftParen::precedence() {
  return 0;
}
