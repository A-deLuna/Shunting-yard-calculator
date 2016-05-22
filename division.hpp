#ifndef DIVISION_HPP
#define DIVISION_HPP

#include "operator_interface.hpp"

class Division : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
  ~Division() {}
};

#endif
