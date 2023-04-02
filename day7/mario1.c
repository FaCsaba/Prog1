#include <stdio.h>

int main(void) {

    unsigned int height = 5;

    for (unsigned int i = 1; i <= height; i++) {
        for (unsigned int j = 1; j < i; j++)
        {
            printf("#");
        }
        printf("#\n");
    }

    return 0;
}