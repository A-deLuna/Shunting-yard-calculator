#ifndef EQUALITY_HPP
#define EQUALITY_HPP

#include "operator_interface.hpp"

class Equality : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
};

#endif

