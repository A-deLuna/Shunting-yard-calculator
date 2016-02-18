#include "substraction.hpp"

long long Substraction::eval(long long a, long long b) {
    return b - a;
}

int Substraction::precedence() {
    return 2;
}

int Substraction::associativity() {
    return assoc::LEFT;
}

