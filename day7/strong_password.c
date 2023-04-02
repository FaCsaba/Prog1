/**
 * Extra credit homework: "Create a strong password!"
 * Fazekas Csaba
 * 2023-03-29 16:13
 * 
 * Create a password that satisfies the following demands:
 * - It must be at least 8 to 12 characters
 * - Contain at least one lower case letter
 * - Contain at least one upper case letter
 * - Contain at least one digit
 * - Contain at least one of the following special characters [.,;']
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

typedef unsigned int uint;

char random_lower() {
    return (char) ((uint) rand() % 26 + 97); 
}

char random_upper() {
    return (char) ((uint) rand() % 26 + 65);
}

char random_digit() {
    return (char) ((uint) rand() % 10 + 48);
}

char random_special() {
    static char specials[] = {'.', ',', ';', '\''};
    return specials[(uint) rand() % 5];
}

typedef char (*random_gen)();

#define BUCKET_LEN 4
static random_gen buckets[BUCKET_LEN] = {random_lower, random_upper, random_digit, random_special}; 

void shuffle(char *array, size_t array_len) {
    if (array_len > 1) {
        size_t i;
        for (i = 0; i < array_len - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (array_len - i) + 1);
          char t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void generate_password(char *password_container, uint password_len) {
    for (uint i = 0; i < password_len; i++) {
        password_container[i] = buckets[i % BUCKET_LEN]();
    }
    shuffle(password_container, password_len);
    password_container[password_len] = '\0';
}

int main(void) {
    // set's up the random seed used later on
    srand(time(NULL));

    uint password_len = 10; // allocating enough memory for a char array
    char *password = (char *) malloc(sizeof(char)*(password_len+1));

    generate_password(password, password_len);

    printf("Password: %s", password);

    free(password);
    return 0;
}
