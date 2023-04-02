#include <iostream>
#include <cmath>

// pure functions

constexpr int fibonacci(int x) {
    return x <= 1 ? x : fibonacci(x-1)+fibonacci(x-2);
}

unsigned int factorial_TR(int x, int y) {
    if (x == 0) return y;
    return factorial_TR(x-1, x*y);
}

unsigned int factorial(int x) {
    return factorial_TR(x, 1);
}

int main(void) {

    std::cout << abs(0.23) << std::endl; // example of a pure function. Most math functions are

    const int a = 10; // example of an immutable var
    const int series = factorial(10);
    std::cout << series << std::endl;

    return 0;
}