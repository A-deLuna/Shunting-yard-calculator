#ifndef NEGATIVE_POWER_HPP
#define NEGATIVE_POWER_HPP

#include "operator_interface.hpp"

class NegativePower : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  char sign() override;
  ~NegativePower() {}
};

#endif
