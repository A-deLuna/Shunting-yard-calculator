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
#include "root.hpp"
#include "equality.hpp"


// global state
std::stack<Number> output_stack;
// TODO refactor to use std::shared_ptr
std::stack<Operator *> operator_stack;

std::map<std::string, Number> var_map;

bool is_number(const std::string & exp);
bool is_variable(const std::string & exp);
Operator* get_operator(const std::string & token, Operator * previous_op, bool boolean_exp);
Operator* get_function_op(const std::string & token);
void evaluate(Operator* op, std::vector<std::string> & out_ops);
void evaluate_function(Operator* op, std::vector<std::string> & out_ops);
void prepare();
Number parse_number(std::string & tok);
Number shunting_yard(std::vector<std::string> & tokens, std::vector<std::string> & out_ops, bool boolean_exp);

Number parse(const std::string & infix_op, std::vector<std::string> & out_ops) {
  std::stringstream stream(infix_op);
  // start previous_op with a dummy value
  // when previous_op is null it means that the last token was not an operation
  std::vector<std::string> tokens = regex(infix_op);
  if(!tokens.empty() && tokens[0] == "FORMATO") {
    if(tokens.size() <= 1) {
      throw std::string("invalid format syntax");
    }
    if(tokens[1] == "FIJO" || tokens[1] == "fijo") {
      Number::formato = Formato::FIJO;
      if(tokens.size() <= 2) throw std::string("invalid format syntax");
    }
    else if(tokens[1] == "REAL" || tokens[1] == "real") {
      Number::formato = Formato::REAL;
    }
    else if(tokens[1] == "NC" || tokens[1] == "nc") {
      Number::formato = Formato::NC;
    }
    else if(tokens[1] == "ESTANDAR" || tokens[1] == "estandar") {
      Number::formato = Formato::ESTANDAR;
    }
    else {
      throw std::string("invalid format syntax");
    }
    return Number("0","0");

  } 
  if(tokens[0] == "SI" && tokens[1] == "[") {
    if(tokens[tokens.size() -1] != ")") {
      throw std::string("error en parentesis");
    }
    bool found_entonces, found_sino = false;
    int i, j;
    // acuerdate que cuando i salga de este loop va a estar incrementado en 1,
    // igual en j AAGUAAANTA CREO QUE ES MENTIRA POR EL BREAK
    for(i = 2; i < tokens.size() - 2; i++) {
      if(tokens[i] == "]" && tokens[i+1] == "ENTONCES" && tokens[i+2] == "(") {
        std::cout << "ENCONTRE ENTONCES!!" << '\n';
        found_entonces = true;
        break;
      }
    }
    for(j = i; j < tokens.size()-2; j++) {
      if(tokens[j] == ")" && tokens[j+1] == "SINO" && tokens[j+2] == "(") {
        std::cout << "ENCONTRE SINO!!" << '\n';
        found_sino = true;
        break;
      }
    }
    if(!found_entonces) {
      throw std::string("syntax error");
    }
    else {
      if(found_sino) {
        std::vector<std::string> copy(&tokens[2], &tokens[i]);
        Number b = shunting_yard(copy, out_ops, true);
        if(!(b == Number("0","0"))) {
          std::cout<<"TRUE" << '\n';
          std::vector<std::string> copy(&tokens[i+3], &tokens[j]);
          return shunting_yard (copy, out_ops, false);
        }
        else {
          std::cout<<"FALSE" << '\n';
          std::vector<std::string> copy(&tokens[j+3], &tokens[tokens.size()-1]);
          return shunting_yard (copy, out_ops, false);
        }
      }
      else {
        std::vector<std::string> copy(&tokens[2], &tokens[i]);
        Number b = shunting_yard(copy, out_ops, true);
        if(!(b == Number("0","0"))) {
          std::cout<<"TRUE" << '\n';
          std::vector<std::string> copy(&tokens[i+3], &tokens[tokens.size()-1]);
          return shunting_yard (copy, out_ops, false);
        }
        else {
          std::cout<<"FALSE" << '\n';
        }
      }
    }
    return Number("0","0");

  }
  return shunting_yard(tokens, out_ops, false);
}

Number shunting_yard(std::vector<std::string> & tokens, std::vector<std::string> & out_ops, bool boolean_exp = false) {
  prepare();
  std::string previous_token;
  Operator * op;
  Operator * previous_op = new Sum();
  std::string last_token = "";
  std::string token;

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
      if(i >= Number("10", "99") || i <= Number("-10", "99")) {
        //std::cout<<i<<'\n'; 
        throw std::string("Number out of valid range");
      }

      if(is_variable(token)) {
        std::stringstream g;
        g << i;
        out_ops.push_back(token + "= " + g.str());
      }
      output_stack.push(i);
      previous_op = nullptr;
    }
    else if((op = get_function_op(token)) != nullptr) {
      operator_stack.push(op);
    }

    else if (token == ",") {
        while(!operator_stack.empty() && operator_stack.top()->sign() != '(') {
          evaluate(operator_stack.top(), out_ops);
          operator_stack.pop();
        }
        // error
        if(operator_stack.empty()) {
          throw std::string("mismatched parens");
        }
    }

    else if((op = get_operator(token, previous_op, boolean_exp)) != nullptr) {
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
        if(!operator_stack.empty() && operator_stack.top()->sign() == 'r') {
          evaluate_function(operator_stack.top(), out_ops);
          operator_stack.pop();
        }
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

    else if(token == "=" && !boolean_exp) {
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

  if(token != "=" && !boolean_exp) {
    throw std::string("Missing =");
  }

  if(!last_token.empty() && !boolean_exp) {
    if(var_map.find(last_token) != var_map.end()) {
      var_map[last_token] = output_stack.top();
      if(tokens[tokens.size()-1] != last_token) {
        throw std::string("Warning, no more expressions after variable assignment");
      }
      // out ops A=
      std::stringstream ss;
      ss << output_stack.top();
      out_ops.push_back(last_token + "= " + ss.str());
      //std::cout << var_map[last_token] << '\n';
    }
    else {
      throw std::string("Warning, no more expressions after =");
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
  // check if E has a point in it
  if(e.find(".") != std::string::npos) {
    throw std::string("E can't have a decimal point");
  }
  int dot_pos = mantissa.find(".");
  if(dot_pos != mantissa.rfind(".")) {
    throw std::string("Multiple dots exception");
  }
  if(dot_pos == mantissa.size()-1) {
    throw std::string("Can't end in dot exception");
  }
  if(dot_pos == 0) {
    mantissa = "0" + mantissa;
  }
  if(dot_pos == std::string::npos) {
    if(mantissa.size() >= 9) {
      throw std::string("Number too long exception");
    }
  }
  else {
    if(mantissa.substr(0, dot_pos).size() >= 9) {
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

Operator* get_operator(const std::string & token, Operator * previous_op, bool boolean_exp) {
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
  else if(token == "=" && boolean_exp) {
    return new Equality();
  }
  else {
    return nullptr;
  }
}
Operator* get_function_op(const std::string & token) {
  if(token == "ROOT" | token == "root") return new Root();
  return nullptr;
}

void evaluate_function(Operator* op, std::vector<std::string> & out_ops) {
  if(output_stack.empty()) {
    throw std::string("Too few operands");
  }
  Number ans;
  std::stringstream s;

  Number a = output_stack.top();
  output_stack.pop();

  if(output_stack.empty()) {
    throw std::string("Too few operands");
  }
  Number b = output_stack.top();
  output_stack.pop();
  ans = op->eval(a, b);
  s << "root(" << b << ", " <<  a << ") = " << ans;
  out_ops.push_back(s.str());
  output_stack.push(ans);
  delete op;
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

  if(ans > Number("9.9999999E99", "0") || ans < Number("-9.9999999E99", "0")) {
    //std::cout<<(ans > Number("9.9999999E99", "0"))<<'\n';
    //std::cout<<(ans < Number("-9.9999999E99", "0"))<<'\n';
    //std::cout<<ans<<'\n'; 
    throw std::string("Number out of valid range2 " );
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
