#include "number.hpp"
#include "iostream"

Number::Number(dec::decimal<8> mantissa, dec::decimal<8> exponent) 
  : mantissa(mantissa), exponent(exponent) {
  normalize();
}

Number::Number(std::string mantissa, std::string exponent) 
  : mantissa(mantissa), exponent(exponent) {
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
  while(mantissa > dec::decimal_cast<8>(0) && mantissa < dec::decimal_cast<8>(1)) {
    shl();
  }
  while(mantissa >= dec::decimal_cast<8>(10)) {
    shr();
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
  Number ans (this->mantissa * b.mantissa , this->exponent + b.exponent);
  return ans;
}

Number Number::operator/(const Number &b) const {
  Number ans (this->mantissa / b.mantissa , this->exponent - b.exponent);
  return ans;
}

Number Number::operator-() const {
  Number n ("-1", "0");
  return *this * n;
}

void Number::shl() {
  mantissa *= dec::decimal_cast<8>(10);
  exponent -= dec::decimal_cast<8>(1);
}
void Number::shr() {
  mantissa /= dec::decimal_cast<8>(10);
  exponent += dec::decimal_cast<8>(1);
}
