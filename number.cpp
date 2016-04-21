#include "number.hpp"
#include <iostream>
#define ROOT_PREC "0.000001"

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

Number Number::operator-() const {
  Number n ("-1", "0");
  return *this * n;
}

bool Number::operator<(const Number &b) const {
  if(this->mantissa == dec::decimal_cast<PREC>(0)) {
    return b.mantissa > dec::decimal_cast<PREC>(0);
  } 

  if(b.mantissa == dec::decimal_cast<PREC>(0)) {
    return this->mantissa < dec::decimal_cast<PREC>(0);
  }

  if(this->exponent < b.exponent) return true;
  if(this->exponent > b.exponent) return false;
  return this->mantissa <  b.mantissa;
}
bool Number::operator==(const Number &b) const {
  return this->exponent == b.exponent && this->mantissa == b.mantissa;
}

Number Number::operator^(const Number &b) {
  
  return pow(*this, b);
}


Number Number::abs(Number n) {
  if(n < Number("0","0")) return -n;
  return n;
}

Number Number::pow(Number x, Number y) {
  if(y == Number(0,0)) {
    Number ans = Number(1,0);
    return ans;
  }
  if(y == Number(1,0)) {
    Number ans = x;
    return ans;
  }
  if(y < Number(0,0)) {
    return pow(Number(1,0) / x, -y);
  }
  if(y.isRational()) {
    Number aux(y);
    aux.toZeroExp();
    dec::int64 before, after;
    aux.mantissa.unpack(before, after);
    bool beganWithZero = before == 0;
    dec::int64 copy;
    int count = 1;
    while(after != 0) {
      aux.mantissa *= dec::decimal_cast<PREC>(10);
      aux.mantissa.unpack(before, after);
      count *= 10;
    }
    copy = before;
    //std::cout<<"COUNT: " << count << '\n';
    //if(!beganWithZero) {
    //  count /= 10;
    //}
    //std::cout<<"COUNT: " << count << '\n';
    //std::cout << x << ":" <<Number(copy,0) << ":" << pow(x, Number(copy, 0)) << " : " << Number(count,0);
    Number e = nthRoot(Number(1,0), x, Number("2","0"));
    //std::cout<< "DEBUG E: " << e <<'\n';
    Number ans = nthRoot(e, pow(x, Number(copy, 0)), Number(count, 0));
    //for(auto & x : powers) {
      //std::cout << x.first.first << "^" << x.first.second << " = " <<  x.second <<'\n';
    //}
    return ans;

  }
  Number ans = Number ("1", "0");
  for(Number i = Number("0","0"); i < y; i = i + Number("1","0")) {
    ans = x * ans;
  }
  return ans;

}
Number Number::nthRoot(Number x, Number a, Number n) {
  // cant take sqrt of negative number
  if(a < Number ("0", "0")) 
    throw std::string("negative sqrt exception");

  Number d = Number(a.exponent,dec::decimal_cast<PREC>(0));
  Number current =  x;
  Number previous = Number("1", "1");
  Number aux = n - Number("1","0");
  do {
    //std::cout<< current;
    previous = current;
    current = (aux * previous + a / pow(previous, aux)) / n;
    //std::cout<<"CALLED NTHROOT" << "\n";
    //std::cout<< ": "<< abs(previous - current)<< "\n";
  } while(abs(previous - current) > Number(ROOT_PREC, "0"));
  return current;

}

bool Number::isRational() const {
  if(this->exponent >= dec::decimal_cast<PREC>(PREC + 1)) {
    return false;
  }
  Number aux(*this);
  aux.toZeroExp();

  dec::int64 before, after;
  aux.mantissa.unpack(before, after);
  if(after == 0) {
    return false;
  }

  return true;
}

void Number::toZeroExp() {
  while(this->exponent < dec::decimal_cast<PREC>(0)) {
    this->shr();
  }

  while(this->exponent > dec::decimal_cast<PREC>(0)) {
    this->shl();
  }
}


void Number::shl() {
  mantissa *= dec::decimal_cast<PREC>(10);
  exponent -= dec::decimal_cast<PREC>(1);
}
void Number::shr() {
  mantissa /= dec::decimal_cast<PREC>(10);
  exponent += dec::decimal_cast<PREC>(1);
}
