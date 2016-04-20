#include "shunting-yard.hpp"

#include <sstream>
#include <iostream>
#include <map>
#include <stack>
#include "operator_interface.hpp"
#include "sum.hpp"
#include "substraction.hpp"
#include "multiplication.hpp"
#include "division.hpp"
#include "negative.hpp"
#include "left-paren.hpp"
#include "right-paren.hpp"
#include "power.hpp"
#include "negative_power.hpp"


// global state
std::stack<Number> output_stack;
// TODO refactor to use std::shared_ptr
std::stack<Operator *> operator_stack;

std::map<std::string, Number> var_map;

bool is_number(const std::string & exp);
bool is_variable(const std::string & exp);
Operator* get_operator(const std::string & token, Operator * previous_op);
void evaluate(Operator* op, std::vector<std::string> & out_ops);
void prepare();
Number parse_number(std::string & tok);

Number parse(const std::string & infix_op, std::vector<std::string> & out_ops) {
  prepare();
  std::stringstream stream(infix_op);
  std::string token;
  std::string previous_token;
  Operator * op;
  // start previous_op with a dummy value
  // when previous_op is null it means that the last token was not an operation
  Operator * previous_op = new Sum();
  std::vector<std::string> tokens = regex(infix_op);
  std::string last_token = "";
  for(auto s = tokens.begin(); s != tokens.end(); ++s) {
    token = *s;
    //std::cout<<token<<std::endl;
    if(is_number(token)) {
      if(is_number(previous_token)) {
        throw std::string("Too many operands");
      }
      if(previous_op && previous_op->sign() == ')') {
        throw std::string("Missing operation between paretheses");
      }
      Number i = parse_number(token);

      if(is_variable(token)) {
        std::stringstream g;
        g << i;
        out_ops.push_back(token + "= " + g.str());
      }
      output_stack.push(i);
      previous_op = nullptr;
    }
    else if((op = get_operator(token, previous_op)) != nullptr) {
      if(op->sign() == '(') {
        if(!previous_op || (previous_op && previous_op->sign() == ')' )) {
          throw std::string("Missing operation between paretheses");
        }
        operator_stack.push(op);
      } else if(op->sign() == ')') {
        while(!operator_stack.empty() && operator_stack.top()->sign() != '(') {
          evaluate(operator_stack.top(), out_ops);
          operator_stack.pop();
        }
        // error
        if(operator_stack.empty()) {
          throw std::string("mismatched parens");
        }
        operator_stack.pop();
      }
      else {
        while(!operator_stack.empty() &&
          ( (op->associativity() == assoc::LEFT && op->precedence() <= operator_stack.top()->precedence())
          ||
          (op->associativity() == assoc::RIGHT && op->precedence() < operator_stack.top()->precedence())))
        {
          evaluate(operator_stack.top(), out_ops);
          operator_stack.pop();
        }
        operator_stack.push(op);
      }
      previous_op = op;
    }
    
    else if(token == "=") {
      if(s+1 != tokens.end())
        last_token = *(s+1);
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
    if(op->sign() == '(') {
      throw std::string("mismatched parens");
    }
    operator_stack.pop();
    evaluate(op, out_ops);
  }

  if(token != "=") {
    throw std::string("Missing =");
  }

  if(!last_token.empty()) {
    if(var_map.find(last_token) != var_map.end()) {
      var_map[last_token] = output_stack.top();
      std::stringstream ss;
      ss << output_stack.top();
      out_ops.push_back(last_token + "= " + ss.str());
      //std::cout << var_map[last_token] << '\n';
    }
  }
  return output_stack.empty() ? Number("0", "0") : output_stack.top();
}

Number parse_number(std::string & tok) {

  if(tok == "A" || tok == "B"||tok == "C") {
    return var_map[tok];
  }
  int e_pos = tok.find("E");

  std::string mantissa;
  std::string e;
  if(e_pos == std::string::npos) {
    mantissa = tok;
    e = "0";
  } else {
    mantissa = tok.substr(0, e_pos);
    e = tok.substr(e_pos+1);
  }
  int dot_pos = mantissa.find(".");
  if(dot_pos != mantissa.rfind(".")) {
    throw std::string("Multiple dots exception");
  }
  if(dot_pos == std::string::npos) {
    if(mantissa.size() >= 11) {
      throw std::string("Number too long exception");
    }
  }
  if(dot_pos == mantissa.size()-1) {
    throw std::string("Can't end in dot exception");
  }
  else {
    if(mantissa.substr(0, dot_pos).size() >= 11) {
      throw std::string("Number too long exception");
    }
  }
  return Number (mantissa, e);

}

bool is_number(const std::string & exp) {
  if(exp.empty()) return false;
  if(exp[0] == '-') return false;
  if(exp == "A" || exp == "B"||exp == "C") return true;
  for (const char & c : exp) {
    if(!(isdigit(c) || c == '.' || c == 'E' || c == '-')) return false;
  }
  return true;
}
bool is_variable(const std::string & exp) {
  if(exp == "A" || exp == "B"||exp == "C") return true;
}
Operator* get_operator(const std::string & token, Operator * previous_op) {
  if(token == "+") {
    return new Sum();
  }
  else if(token == "-") {
    if(previous_op && previous_op->sign() != '_' && previous_op->sign() != ')') {
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
  else if(token == "(") {
    return new LeftParen();
  }
  else if(token == ")") {
    return new RightParen();
  }
  else if(token == "^") {
    if(previous_op && previous_op->sign() == ')') {
      return new Power();
    }
    else {
      return new NegativePower();
    }
  }
  else {
    return nullptr;
  }
}

void evaluate(Operator* op, std::vector<std::string> & out_ops) {
  if(output_stack.empty()) {
    throw std::string("Too few operands");
  }
  Number a = output_stack.top();

  output_stack.pop();
  std::stringstream s;

  Number ans;
  if(op->arity() == 1) {
    Number n ("0", "0");
    ans = op->eval(a, n);
    s <<  "-" <<  a << " = " << ans;
    out_ops.push_back(s.str());
  }
  else {
    if(output_stack.empty()) {
      throw std::string("Too few operands");
    }
    Number b = output_stack.top();
    output_stack.pop();
    ans = op->eval(a, b);
    s << b << " " << op->sign() << " " <<  a << " = " << ans;
    out_ops.push_back(s.str());
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
  // this is a hack to make sure we have initialized every variable
  // whenevery you access a map key with no value it is initialized by default
  var_map["A"];
  var_map["B"];
  var_map["C"];
}
