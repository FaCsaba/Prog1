#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef unsigned int uint;

uint char_count(char *str, char ch) {
    uint test_str_len = strlen(str);
    uint ch_amount = 0;

    for(uint i = 0; i < test_str_len; i++) {
        if (str[i] == ch) {
            ch_amount++;
        }
    }
    return ch_amount;
}

int main(void) {

    char *test1 = "Abba";
    printf("%d\n", char_count(test1, 'b'));

    assert(char_count(test1, 'b') == 2 && "There are two b's in this");
    assert(char_count(test1, 'x') == 0 && "There are 0 x's in this");

    return 0;
}