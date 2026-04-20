#include "dyn_array.h"
#include <stdio.h>

int main() {
    int_array *numbers = int_new(); //Declaring a dynamic array

    int_add(numbers, 5);
    int_add(numbers, 2);
    int_add(numbers, 7);

    for (int i = 0; i < int_size(numbers); i++) {
        printf("%d\n", numbers->data[i]);
    }

    int_free(numbers);
}