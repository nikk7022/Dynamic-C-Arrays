/* === Copyright © 2026 <Nikola K.> === */

/* You are allowed to do whatever your mind allows 
you to do with this just keep this header here and
you're good to go. */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdio.h>

#define DEFINE_ARRAY(t) \
\
struct t##_array_s; \
\
typedef struct t##_array_s {   \
    t *data;                   \
    struct t##_array_s **nest; \
    int cap;                   \
    int size;                  \
    int nest_cap;              \
    int nest_size;             \
} t##_array;                   \
\
static t##_array* t##_new() {                     \
    t##_array *array = malloc(sizeof(t##_array)); \
    if (!array) return NULL;                      \
    array->data = malloc(4 * sizeof(t));          \
    array->cap = 4;                               \
    array->size = 0;                              \
    array->nest = malloc(4 * sizeof(t##_array*)); \
    array->nest_cap = 4;                          \
    array->nest_size = 0;                         \
    else return array;                            \
}                                                 \
\
static void t##_free(t##_array *array) {  \
    free(array->data);                           \
    for (int i = 0; i < array->nest_size; i++) { \
        t##_free(array->nest[i]);                \
    }                                            \
    free(array->nest);                           \
    free(array);                                 \
}                                                \
\
static void t##_resize(t##_array *array) {                          \
    if (array->size >= array->cap) {                                \
        array->cap *= 2;                                            \
        array->data = realloc(array->data, array->cap * sizeof(t)); \
    } else if (array->size < array->cap / 4 && array->cap > 4) {    \
        array->cap /= 2;                                            \
        array->data = realloc(array->data, array->cap * sizeof(t)); \
    }                                                               \
}                                                                   \
\
static void t##_add(t##_array *array, t value) { \
    t##_resize(array);                           \
    array->data[array->size] = value;            \
    array->size++;                               \
}                                                \
\
static void t##_remove(t##_array *array, int index) { \
    for (int i = index; i < array->size - 1; i++) {   \
        array->data[i] = array->data[i + 1];          \
    }                                                 \
    array->size--;                                    \
    t##_resize(array);                                \
}                                                     \
\
static void t##_insert(t##_array *array, t value, int index) { \
    t##_resize(array);                                         \
    for (int i = array->size; i > index; i--) {                \
        array->data[i] = array->data[i - 1];                   \
    }                                                          \
    array->data[index] = value;                                \
    array->size++;                                             \
}                                                              \
\
static inline void t##_clear(t##_array *array) { \
    array->size = 0;                             \
}                                                \
\
static inline int t##_size(t##_array *array) { \
    return array->size;                        \
}                                              \
\
static inline t t##_value(t##_array *array, int index) { \
    return array->data[index];                           \
}                                                        \
\
static inline t* t##_pointer(t##_array *array) { \
    return array->data;                          \
}                                                \
\
static void t##_nest_resize(t##_array *array) {                                   \
    if (array->nest_size >= array->nest_cap) {                                    \
        array->nest_cap *= 2;                                                     \
        array->nest = realloc(array->nest, array->nest_cap * sizeof(t##_array*)); \
    } else if (array->nest_size < array->nest_cap / 4 && array->nest_cap > 4) {   \
        array->nest_cap /= 2;                                                     \
        array->nest = realloc(array->nest, array->nest_cap * sizeof(t##_array*)); \
    }                                                                             \
}                                                                                 \
\
static void t##_nest(t##_array *array, t##_array *array2) { \
    t##_nest_resize(array);                                 \
    array->nest[array->nest_size] = array2;                 \
    array->nest_size++;                                     \
}                                                           \
\
static t##_array* t##_copy(t##_array *array) {         \
    t##_array *copyarray = t##_new();                  \
    for (int i = 0; i < array->size; i++) {            \
        t##_add(copyarray, array->data[i]);            \
    }                                                  \
    for (int i = 0; i < array->nest_size; i++) {       \
        t##_nest(copyarray, t##_copy(array->nest[i])); \
    }                                                  \
    return copyarray;                                  \
}                                                      \
\
static void t##_unnest(t##_array *array, int index, t##_array **newarray) { \
    *newarray = array->nest[index];                                         \
    for (int i = index; i < array->nest_size - 1; i++) {                    \
        array->nest[i] = array->nest[i + 1];                                \
    }                                                                       \
    array->nest_size--;                                                     \
    t##_nest_resize(array);                                                 \
}                                                                           \
\
static void t##_denest(t##_array *array, int index) {        \
    t##_free(array->nest[index]);                            \
    for (int i = index; i < array->nest_size - 1; i++) {     \
        array->nest[i] = array->nest[i + 1];                 \
    }                                                        \
    array->nest_size--;                                      \
    t##_nest_resize(array);                                  \
}                                                            \
\
static inline void t##_clearnest(t##_*array, int ) { \
    t##_array->nest_size = 0;                        \
}                                                    \
\

DEFINE_ARRAY(int)
DEFINE_ARRAY(short)
DEFINE_ARRAY(long)
DEFINE_ARRAY(float)
DEFINE_ARRAY(double)
DEFINE_ARRAY(char)

static void string_input(char_array *array) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        char_add(array, (char)c);
    }

    char_add(array, '\0');
}

static void string_set(char_array *array, const char *string) {
    array->size = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        char_add(array, string[i]);
    }

    char_add(array, '\0');
}

static void string_add(char_array *array, char_array *array2) {
    array->size--;

    for (int i = 0; i < array2->size; i++) {
        char_add(array, array2->data[i]);
    }

    char_add(array, '\0');
}

static void string_insert(char_array *array, char_array *array2, int index) {
    for (int i = 0; i < array->size; i++) {
        if (i == index) {
            for (int j = 0; j < array2->size; j++) {
                if (array2->data[j] != '\0') {
                    char_insert(array, array2->data[j], i);
                    i++;
                }
            }
        }
    }
}

#endif