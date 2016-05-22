#ifndef AND_HPP
#define AND_HPP

#include "operator_interface.hpp"

class And : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
};

#endif

