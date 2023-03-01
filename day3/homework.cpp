#include <iostream>
#define arr_len 10

/**
 * Source: https://www.geeksforgeeks.org/bubble-sort/
*/
void bubble_sort(int* arr, int len) {
    int i, j;
    for (i = 0; i < len; i++) {
        for (j = 0; j < len - i; j++) {
            if (*(arr+j) > *(arr+j+i)) {
                std::swap(*(arr+j), *(arr+j+i));
            }
        }
    }
}

// Bubble sort algorithm
int main(void) {
    int arr[arr_len] = {1, 2, 3, 5, 4, 12, 7, 6, 5, 10};
    bubble_sort(arr, arr_len);
    for (int i = 0; i < arr_len; i++) {
        std::cout << *(arr+i) << std::endl;
    }
    return 0;
}