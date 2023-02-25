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

    // find all powers of two looping up to 300
    int i = 0;
    int powed = 0;
    while (true) {
        powed = pow(2, i);
        if (powed > 300) {break;}
        std::cout << "Power of two: " << powed << std::endl;
        i++;
    }
    

    return 0;
}