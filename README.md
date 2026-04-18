# Dynamic arrays for C

This library allows you to create and control dynamic arrays.
All you have to do is put `dyn_array.h` inside your project folder and include it with directive.

```c
#include "dyn_array.h"
```

### Features:
- Automatic resizing
- Type-specific arrays
- Nesting other arrays into an array
- Dynamic strings control for character arrays
- Compatible with standard `string.h` library functions

### Functions:

```c
type_array* type_new(void);
type_array* type_copy(type_array *array);
void        type_free(type_array *array);
void        type_add(type_array *array, type element);
void        type_remove(type_array *array, int index);
void        type_insert(type_array *array, type element, int index);
void        type_nest(type_array *array, type_array *nested);
void        type_unnest(type_array *array, int index, type_array **newarray);
void        type_denest(type_array *array, int index);

/*Only char arrays*/
void        string_input(char_array *array);
void        string_set(char_array *array, const char *string);
void        string_add(char_array *array, char_array *array2);
void        string_insert(char_array *array, char_array *array2, int index);

/*Optional*/
int         type_size(type_array *array);               /*replacement*/ array->size
int         type_nest_size(type_array *array);          /*replacement*/ array->nest_size
type        type_value(type_array *array, int index);   /*replacement*/ array->data[index]
type*       type_pointer(type_array *array);            /*replacement*/ array->data / array->nest[index]
```

### Memory Management
You must call `type_free()` for every array you create to avoid memory leaks.
Each array allocates memory dynamically, which is not freed automatically.

### Usage examples:

#### Example 1: Basic declaration and print
```c
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
```
#### Example 2: Basic nesting and print
```c
#include "dyn_array.h"
#include <stdio.h>

int main() {
    int_array *groups = int_new();

    int_array *group1 = int_new();
    int_array *group2 = int_new();

    int_add(group1, 4);
    int_add(group1, 8);
    int_add(group1, 10);
    int_add(group1, 13);

    int_add(group2, 3);
    int_add(group2, 7);
    int_add(group2, 12);
    int_add(group2, 18);

    int_nest(groups, group1);
    int_nest(groups, group2);

    for (int i = 0; i < int_nest_size(groups); i++) {
        for (int j = 0; j < int_size(groups->nest[i]); j++) {
            printf("%d\n", groups->nest[i]->data[j]);
        }
    }

    int_free(groups); // All nested arrays of `groups` array are freed as well
}
```

#### Example 3: Declaring and printing a string
```c
#include "dyn_array.h"
#include <stdio.h>

int main() {
    char_array *string = char_new();
    string_set(string, "Hello World!");
    printf("%s", string->data);

    char_free(string);
}
```

#### Example 4: String input and print
```c
#include "dyn_array.h"
#include <stdio.h>

int main() {
    char_array *name = char_new();
    string_input(name);
    printf("%s", name->data);

    char_free(name);
}
```
