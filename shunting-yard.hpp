#ifndef SHUNTING_YARD_HPP
#define SHUNTING_YARD_HPP

#include <string>
#include <vector>
#include "number.hpp"

Number parse(const std::string & infix_op, std::vector<std::string> & out_ops);
std::vector<std::string> regex(const std::string & infix_op);
std::string toBase(long long n, int base);
#endif
