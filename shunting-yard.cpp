#include "shunting-yard.hpp"

#include <sstream>
#include <iostream>
#include <stack>
#include "operator_interface.hpp"
#include "sum.hpp"
#include "substraction.hpp"
#include "multiplication.hpp"
#include "division.hpp"
#include "memory"

// TODO:(tony) roll my own number data type to accomodate
// for project constrains 
// comment to previos todo, maybe its not necessary... we could 
// handle the logic in the eval methods, it's worth a thought later
std::stack<long long> output_stack;
std::stack<Operator *> operator_stack;

bool is_number(const std::string & exp) {
  for (const char & c : exp) {
    if(!isdigit(c)) return false;
  }
  return true;
}

Operator* get_operator(std::string s) {
  if(s == "+") {
    return new Sum();
  }
  else if(s == "-") {
    return new Substraction();
  }
  else if(s == "*") {
    return new Multiplication();
  }
  else if(s == "/") {
    return new Division();
  }
  else {
    return nullptr;
  }
}

void evaluate(Operator* op) {
  if(output_stack.empty()) {
    throw "Too few operands";
  }
  int a = output_stack.top();
  output_stack.pop();

  if(output_stack.empty()) {
    throw "Too few operands";
  }
  long long b = output_stack.top();
  output_stack.pop();
  // std::cout<<"evaluating with arguments "<<a << ", " << b<<"\n";
  long long ans = op->eval(a, b);
  // std::cout<<"eval ans = "<<ans<<std::endl;
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

long long parse(std::string infix_op) {
  // output_stack.clear();
  // operator_stack.clear();
  prepare();
  std::stringstream stream(infix_op);
  std::string s;
  Operator * op;

  while(stream >> s) {
    if(is_number(s)) {
      long long i = stoll(s);
      if(i > MAX_NUM) {
        throw "Integer Overflow";
      }
      output_stack.push(i);
      // std::cout<<"pushed "<<s<<"\n";
    }
    if((op = get_operator(s)) != nullptr) {
      // std::cout<<"found operator "<<s<<"\n";
      while(!operator_stack.empty() && 
              (
               (op->associativity() == assoc::LEFT && op->precedence() <= operator_stack.top()->precedence())
              || 
              (op->associativity() == assoc::RIGHT && op->precedence() < operator_stack.top()->precedence())
              )
            )
      {
        // std::cout<<"condition met, evaluating "<<std::endl;
        evaluate(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.push(op);
    }
  }

  while(!operator_stack.empty()) {
    op = operator_stack.top();
    operator_stack.pop();
    evaluate(op);
  }
  
  // std::cout<<"answer "<< output_stack.top() <<"\n";
  return output_stack.top();
}



