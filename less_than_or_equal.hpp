#ifndef LESS_THAN_OR_EQUAL
#define LESS_THAN_OR_EQUAL

#include "operator_interface.hpp"

class LessThanOrEqual : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  char sign() override;
};

#endif

