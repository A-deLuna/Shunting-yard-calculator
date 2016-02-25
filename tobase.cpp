#include "shunting-yard.hpp"
#include <iostream>
std::string toBase(long long n, int base) {
    std::string ans = "";
    char simbols[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    bool isNeg = false;
    if(n < 0) {
        isNeg = true;
        n = (n ^ (~0LL)) + 1;
        std::cout <<" ~0LL " << ~0LL <<std::endl;
        std::cout <<" n ^ ~0LL " << (n ^ (~0LL)) << std::endl;
        std::cout <<" new n = " << n <<std::endl;
    }
    while(n) {
        ans = simbols[n % base] + ans;
        n /= base;
    }
    return ans;
}
