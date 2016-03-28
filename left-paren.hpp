#ifndef LEFT_PAREN_HPP
#define LEFT_PAREN_HPP

#include "operator_interface.hpp"

class LeftParen: public Operator {
public: 
  char sign() override;
  int associativity() override;
  int precedence() override;
};

#endif
