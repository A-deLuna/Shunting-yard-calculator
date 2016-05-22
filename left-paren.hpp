#ifndef LEFT_PAREN_HPP
#define LEFT_PAREN_HPP

#include "operator_interface.hpp"

class LeftParen: public Operator {
public: 
  std::string sign() override;
  int associativity() override;
  int precedence() override;
};

#endif
