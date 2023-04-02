#include <stdio.h>
#define ARR_LEN 10

void array_abs(int *arr, unsigned int arr_len) {
    for (unsigned int i = 0; i < arr_len; i++) {
        arr[i] = arr[i] > 0 ? arr[i] : -arr[i]; 
    }
}

void array_print(int *arr, unsigned int arr_len) {
    for (unsigned int i = 0; i < arr_len; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
}

int main(void) {
    
    int array[ARR_LEN] = {1, -3, -234, 75, -34, 69, 420, -55, 0, 34};
    
    array_print(array, ARR_LEN);

    array_abs(array, ARR_LEN);

    array_print(array, ARR_LEN);

    return 0;
}

