#ifndef OPERATOR_INTERFACE_HPP
#define OPERATOR_INTERFACE_HPP

#define MAX_NUM 999999999999LL
#define MIN_NUM -999999999999LL
#include "number.hpp"
#include <string>

enum assoc {NONE, LEFT, RIGHT };

class Operator {
public:
  virtual Number eval(Number a, Number b) {}
  virtual int precedence() {}
  virtual int associativity() {}
  virtual int arity() {}
  virtual std::string sign() {}
  virtual ~Operator() {}
};
#endif
