#ifndef NOT_EQUAL_HPP
#define NOT_EQUAL_HPP

#include "operator_interface.hpp"

class NotEqual : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
};

#endif

