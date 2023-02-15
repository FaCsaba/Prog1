#include <iostream>

char *g = "Wow! This is a global variable";

// preprocessor directive, replace LENGTH with 69
#define LENGTH 69

int main() {
    std::cout << "Hello, World!\n";
    
    // simple types
    char c = 'c';       // Character literal
    int i = 0;          // 32bit signed integer
    short int si = 1;   // 16bit signed integer
    long int li = 2;    // 64bit signed integer
    float f = 78.9;     // floating number
    double d = 78.9;    // double precision floating number
    bool b = false;

    int i1, i2, i3;     // declaring multiple
    char x,y;

    std::cout << "char: " << sizeof(char) << std::endl;
    std::cout << "int: " << sizeof(int) << std::endl;
    std::cout << "short int: " << sizeof(short int) << std::endl;
    std::cout << "long int: " << sizeof(li) << std::endl;
    std::cout << "float: " << sizeof(float) << std::endl;
    std::cout << "double: " << sizeof(double) << std::endl;
    std::cout << "bool: " << sizeof(bool) << std::endl;
    
    /**
     * Többsoros!!
    */

    typedef int egesz; // declare types

    std::cout << g << std::endl;
    char *g = "Local :)";
    std::cout << g << std::endl;

    { // block
            char *g = "wowow even more local :)";
            std::cout << g << std::endl;
    }
    std::cout << g << std::endl;

    std::cout << "\\ \?" << std::endl; // just like most other languages \ is an escape character
    // special character
    // \ esc
    // " string literal
    // ' character literal
    // ? this is stupid I have no idea why we say this is a special character
    // a alert
    // n newline
    // b backspace
    // f form-feed
    // n new-line
    // r carrige return
    // t tab
    // v vertical tab

    std::cout << LENGTH << std::endl;

    const int width = 4;

    // width = 5; // this will not compile

    // Operators
    // + - * / % ++ --
    
    // Equivalence operators
    // == != <= >= < >
    // &&, ||, & bitwise and, | bitwise or
    // ^ xor, << bitshift left, >> bitshift right

    int A = 60;
    int B = 13;

    std::cout << (A <<2) << std::endl; // precedents is on the printf, use brackets in this case

    int arr[LENGTH] = {1,2,3,4,5}; // I think most compilers will just zero the other values out

    std::cout << *(arr+5) << std::endl;

    return 0;
}