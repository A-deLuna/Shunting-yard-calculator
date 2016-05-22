#ifndef SUBSTRACTION_HPP
#define SUBSTRACTION_HPP

#include "operator_interface.hpp"

class Substraction : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
  ~Substraction() {}
};

#endif
