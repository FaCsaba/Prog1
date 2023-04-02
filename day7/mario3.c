#include <stdio.h>

typedef unsigned int uint;

int main(void) {

    uint height = 5;

    for (int i = 1; i <= height; i++) {
        
        for (int j = 0; j < height-i; j++) {
            putchar(' ');
        }
        for (int j = 0; j < i; j++) {
            putchar('#');
        }

        printf("  ");

        for (uint j = 0; j < i; j++) {
            putchar('#');
        }
        puts("");

    }


    return 0;
} 