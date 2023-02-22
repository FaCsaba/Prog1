#include<iostream>
#include<vector>

int main(void) {

        int numbers[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9,  10, 11, 12}
    };

    // homework
    // 1 2 3 4
    // 5 6 7 8
    // 9 10 11 12

    // Get the biggest value of the row
    int max;
    int current;
    for (int i = 0; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
        max = INT_MIN;
        for (int j = 0; j < sizeof(numbers[0])/sizeof(int); j++) {
            current = numbers[i][j];
            if (max < current) {
                max = current;
            }
        }
        std::cout << "Max of row: " << max << std::endl;
    }

    // Get the biggest value in the 2d array flat
    max = 0;
    for (int i = 0; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
        for (int j = 0; j < sizeof(numbers[0])/sizeof(int); j++) {
            current = numbers[i][j];
            if (max < current) {
                max = current;
            }
        }
    }

    // find all the numbers divisible by 3 while looping down from 100
    for (int i = 100; i > 0; i--) {
        if (i % 3 == 0) {
            std::cout << "Divisible by 3: " << i << std::endl;
        }
    }

    double logged;
    for (int i = 0; i < 300; i++) {
        logged = log2(i);
        if (floor(logged) == logged) { // check if double is a whole number
            std::cout << "Power of 2: " << i << std::endl;
        }
    }

    return 0;
}