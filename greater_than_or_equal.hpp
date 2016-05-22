#ifndef GREATER_THAN_OR_EQUAL
#define GREATER_THAN_OR_EQUAL

#include "operator_interface.hpp"

class GreaterThanOrEqual : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
};

#endif

