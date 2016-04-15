#include "number.hpp"
#include <iostream>

Number::Number(dec::decimal<PREC> mantissa, dec::decimal<PREC> exponent) 
  : mantissa(mantissa), exponent(exponent) {
  normalize();
}

Number::Number(std::string mantissa, std::string exponent) {
    int e_pos = mantissa.find("E");

    if(e_pos == std::string::npos) {
        this->mantissa = dec::decimal<PREC>(mantissa);
        this->exponent = dec::decimal<PREC>(exponent);
    }
    else {
      std::string mant = mantissa.substr(0, e_pos);
      std::string exp = mantissa.substr(e_pos+1);
      this->mantissa = dec::decimal<PREC>(mant);
      this->exponent = dec::decimal<PREC>(exp);
    }
  normalize();
}

Number::Number(int mantissa, int exponent) 
  : mantissa(mantissa), exponent(exponent) {
  normalize();
}
Number::Number() 
  : mantissa(0), exponent(0) {
}

void Number::normalize() {
  while(mantissa > dec::decimal_cast<PREC>(0) && mantissa < dec::decimal_cast<PREC>(1)) {
    shl();
  }
  while(mantissa >= dec::decimal_cast<PREC>(10) || mantissa <= dec::decimal_cast<PREC>(-10)) {
    shr();
  }
  // this fix is for the case 0.3333333 - 1/3 which has mantssa 0 but exponent -1
  if( mantissa == dec::decimal_cast<PREC>(0)) {
    exponent = dec::decimal_cast<PREC>(0);
  }
}

Number Number::operator+(const Number &b) const {
  Number smlr = std::min(*this, b);
  Number gtr = std::max(*this, b);

  while(smlr.exponent < gtr.exponent) {
    smlr.shr();
  }

  Number ans(gtr.mantissa + smlr.mantissa, gtr.exponent);
  return ans;
}

Number Number::operator-(const Number &b) {
  Number b_cpy(b);
  Number * smlr =  (*this < b_cpy) ? this : &b_cpy;
  Number gtr = std::max(*this, b_cpy);

  while(smlr->exponent < gtr.exponent) {
    smlr->shr();
  }

  Number ans(this->mantissa - b_cpy.mantissa, gtr.exponent);
  return ans;
}

Number Number::operator*(const Number &b) const {
  //std::cout<< this -> mantissa << ": E" << this->exponent << "\n"; 
  //std::cout<< b.mantissa << ": E" <<b.exponent << "\n"; 
  Number ans (this->mantissa * b.mantissa , this->exponent + b.exponent);
  //std::cout<< ans.mantissa << ": E" <<ans.exponent << "\n"; 
  return ans;
}

Number Number::operator/(const Number &b) const {
  Number ans (this->mantissa / b.mantissa , this->exponent - b.exponent);
  return ans;
}

Number Number::abs(Number n) {
  if(n < Number("0","0")) return -n;
  return n;
}

Number Number::sqrt(Number a) {
  // cant take sqrt of negative number
  if(a < Number ("0", "0")) 
    throw std::string("negative sqrt exception");

  Number current = a;
  Number previous = Number("1", "1");
  do {
    previous = current;
    current = (previous + a / previous) / Number("2", "0");
  } while(abs(previous - current) > Number("0.0000001", "0"));
  return current;

}

Number Number::factorial (int n) {
  if(n == 0) return Number ("1", "0");
  if(n == 1) return Number ("1", "0");
  return Number(n, 0) * factorial(n-1);
}

Number Number::exp(Number a, Number b) {
  if(b < Number("0", "0")) return exp(Number("1","0") / a, -b);
  if(b == Number("0","0")) return Number("1","0");
  if(b == Number("1","0")) return a;

  return a * exp(a , b - Number("1", "0"));
}

Number Number::decimalExp(Number power) {
  int ITERS = 27;
  Number result("1","0");
  for(int iter = 0; iter < 27; iter++ ) {
    Number factoria = factorial(iter);
    result = result + exp(power, Number(iter, 0)) / factoria;
  }
  std::cout << result
  return result;
}

Number Number::LogN(Number number) {
  Number aux = number - Number(1, 0);

  Number result = Number(0,0);

  for(int iter = 1; iter < 27; iter++) {
    if(iter % 2 == 0) {
      result = result - exp(aux, Number(iter,0)) / Number(iter,0);
    }
    else {
      result = result + exp(aux, Number(iter,0)) / Number(iter,0);
    }
  }
  return result;
}

Number Number::pow(Number a, Number b) {

  return decimalExp(b * LogN(a));
}

Number Number::operator^(const Number &b) {
  
  return pow(*this, b);
}

Number Number::operator-() const {
  Number n ("-1", "0");
  return *this * n;
}

void Number::shl() {
  mantissa *= dec::decimal_cast<PREC>(10);
  exponent -= dec::decimal_cast<PREC>(1);
}
void Number::shr() {
  mantissa /= dec::decimal_cast<PREC>(10);
  exponent += dec::decimal_cast<PREC>(1);
}
