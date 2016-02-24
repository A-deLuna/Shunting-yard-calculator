#include "shunting-yard.hpp"

#include <sstream>
#include <iostream>
#include <stack>
#include "operator_interface.hpp"
#include "sum.hpp"
#include "substraction.hpp"
#include "multiplication.hpp"
#include "division.hpp"
#include "negative.hpp"

// TODO:(tony) roll my own number data type to accomodate
// for project constrains
// comment to previos todo, maybe its not necessary... we could
// handle the logic in the eval methods, it's worth a thought later
// Yet another entry... I've been thinking about using a fixed decimal data type
// to hold the numbers


// global state
std::stack<long long> output_stack;
// TODO refactor to use std::shared_ptr
std::stack<Operator *> operator_stack;

bool is_number(const std::string & exp);
Operator* get_operator(const std::string & token, Operator * previous_op);
void evaluate(Operator* op, std::vector<std::string> & out_ops);
void prepare();

long long parse(const std::string & infix_op, std::vector<std::string> & out_ops) {
  prepare();
  std::stringstream stream(infix_op);
  std::string token;
  std::string previous_token;
  Operator * op;
  // start previous_op with a dummy value
  // when previous_op is null it means that the last token was not an operation
  Operator * previous_op = new Sum();
  std::vector<std::string> tokens = regex(infix_op);
  for(auto s = tokens.begin(); s != tokens.end(); ++s) {
    token = *s;
    if(is_number(token)) {
      if(is_number(previous_token)) {
        throw std::string("Too many operands");
      }
      long long i = stoll(token);
      if(i > MAX_NUM) {
        throw std::string("Integer Overflow");
      }
      output_stack.push(i);
      previous_op = nullptr;
    }
    else if((op = get_operator(token, previous_op)) != nullptr) {
      while(!operator_stack.empty() &&
              (
               (op->associativity() == assoc::LEFT && op->precedence() <= operator_stack.top()->precedence())
              ||
              (op->associativity() == assoc::RIGHT && op->precedence() < operator_stack.top()->precedence())
              )
            )
      {
        evaluate(operator_stack.top(), out_ops);
        operator_stack.pop();
      }
      previous_op =  op;
      operator_stack.push(op);
    }
    else if(token == "=") {
      break;
    }
    // unknown token
    else {
      throw std::string("Unexpected Token '" + token + "'");
    }
    previous_token = token;
  }

  while(!operator_stack.empty()) {
    op = operator_stack.top();
    operator_stack.pop();
    evaluate(op, out_ops);
  }

  if(token != "=") {
    throw std::string("Missing =");
  }
  return output_stack.top();
}

bool is_number(const std::string & exp) {
  if(exp.empty()) return false;
  for (const char & c : exp) {
    if(!isdigit(c)) return false;
  }
  return true;
}
Operator* get_operator(const std::string & token, Operator * previous_op) {
  if(token == "+") {
    return new Sum();
  }
  else if(token == "-") {
    if(previous_op && (previous_op->sign() != '_')) {
      return new Negative();
    }
    return new Substraction();
  }
  else if(token == "*") {
    return new Multiplication();
  }
  else if(token == "/") {
    return new Division();
  }
  else {
    return nullptr;
  }
}

void evaluate(Operator* op, std::vector<std::string> & out_ops) {
  if(output_stack.empty()) {
    throw std::string("Too few operands");
  }
  int a = output_stack.top();
  output_stack.pop();

  long long ans;
  if(op->arity() == 1) {
    ans = op->eval(a, 0);
    out_ops.push_back( "-" + std::to_string(a) + " = " + std::to_string(ans));
  }
  else {
    if(output_stack.empty()) {
      throw std::string("Too few operands");
    }
    long long b = output_stack.top();
    output_stack.pop();
    ans = op->eval(a, b);
    out_ops.push_back(std::to_string(b) + " " + op->sign() + " " +  std::to_string(a) + " = " + std::to_string(ans) );
  }

  output_stack.push(ans);
  delete op;
}

void prepare() {
  while(!output_stack.empty()) {
    output_stack.pop();
  }
  while(!operator_stack.empty()) {
    operator_stack.pop();
  }
}
