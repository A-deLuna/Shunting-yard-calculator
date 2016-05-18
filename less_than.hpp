#ifndef LESS_THAN_HPP
#define LESS_THAN_HPP

#include "operator_interface.hpp"

class LessThan : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  char sign() override;
};
#endif
