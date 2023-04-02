#include <stdio.h>

int main(void) {

    for (int i = 32; i < 128; i++) {
        printf("%03d: %c\n", i, i);
    }

    return 0;
}