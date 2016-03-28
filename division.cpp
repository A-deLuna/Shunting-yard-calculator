#include "division.hpp"
#include <string>

Number Division::eval(Number a, Number b) {
//  if(a == 0) {
//    throw std::string("Division by zero");
// }
  return b / a;
}

int Division::precedence() {
  return 3;
}

int Division::associativity() {
  return assoc::LEFT;
}

int Division::arity() {
    return 2;
}

char Division::sign() {
  return '/';
}
