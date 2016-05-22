#ifndef NEGATIVE_HPP
#define NEGATIVE_HPP

#include "operator_interface.hpp"

class Negative : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
  ~Negative() {}
};

#endif
