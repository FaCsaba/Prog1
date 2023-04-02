#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef unsigned int uint;

bool is_palindrome(const char *str) {
    uint str_len = strlen(str);
    for (uint i = 0; i < str_len / 2; i++) {
        if (str[i] != str[str_len-i-1]) {
            return false;
        }
    }
    return true;
}




int main(void) {
    char *s = "radar";
    assert(is_palindrome(s) && "radar is palindrome");
    printf("%s is palindrome?: %s\n", s, is_palindrome(s) ? "yes" : "no");
    
    s = "";
    assert(is_palindrome(s) && " is palindrome");
    printf("%s is palindrome?: %s\n", s, is_palindrome(s) ? "yes" : "no");

    assert(is_palindrome("aa") && "aa is palindrome");
    return 0;
}