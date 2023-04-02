#include <stdio.h>
#define uint unsigned int

int main(void) {

    uint height = 4;

    for (int i = 1; i <= height; i++) {
        
        for (int j = 0; j < height-i; j++) {
            putchar(' ');
        }
        for (int j = 0; j < i; j++) {
            putchar('#');
        }
        puts("");
    }

    return 0;
}
