#ifndef OR_HPP
#define OR_HPP

#include "operator_interface.hpp"

class Or : public Operator {
public:
  Number eval(Number a, Number b) override;
  int precedence() override;
  int associativity() override;
  int arity() override;
  std::string sign() override;
};

#endif
