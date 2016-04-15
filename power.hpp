#ifndef POWER_HPP
#define POWER_HPP

#include "operator_interface.hpp"

class Power : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  char sign() override;
  ~Power() {}
};

#endif
