#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "vec.h"

static void rpanic(void) { abort(); }

static void* my_malloc(const size_t size) {
    void* const res = malloc(size);
    if (!res) rpanic();
    return res;
}

static void* my_realloc(void* const ptr, const size_t size) {
    void* const res = realloc(ptr, size);
    if (!res) rpanic();
    return res;
}

struct Vec {
    size_t elem_size;
    size_t len;
    size_t cap;
    void* data;
};

static const void* vec_at_unchecked(const Vec* const vec, const size_t i) {
    return (char*)vec->data + vec->elem_size * i;
}

static void* vec_at_mut_unchecked(const Vec* const vec, const size_t i) {
    return (char*)vec->data + vec->elem_size * i;
}

Vec* vec_new(const size_t elem_size, const size_t len, const void* const value) {
    const size_t cap = len == 0 ? 1 : len;

    Vec* vec = vec_with_capacity(elem_size, cap);
    vec->len = len;

    for (size_t i = 0; i < len; ++i)
        memcpy(vec_at_mut_unchecked(vec, i), value, elem_size);

    return vec;
}

Vec* vec_with_capacity(const size_t elem_size, size_t cap) {
    if (cap == 0) cap = 1;

    Vec* vec = (Vec*)my_malloc(sizeof(Vec));
    vec->elem_size = elem_size;
    vec->len = 0;
    vec->cap = cap;
    vec->data = my_malloc(elem_size * cap);

    return vec;
}

void vec_delete(Vec* const vec) {
    free(vec->data);

    vec->elem_size = 0;
    vec->len = 0;
    vec->cap = 0;
    vec->data = NULL;

    free(vec);
}

void vec_clear(Vec* const vec) {
    vec->len = 0;
}

bool vec_is_empty(const Vec* const vec) {
    return vec->len == 0;
}

size_t vec_len(const Vec* const vec) {
    return vec->len;
}

size_t vec_capacity(const Vec* const vec) {
    return vec->cap;
}

const void* vec_data(const Vec* const vec) {
    return vec->data;
}

void* vec_data_mut(const Vec* const vec) {
    return vec->data;
}

const void* vec_front(const Vec* const vec) {
    assert(!vec_is_empty(vec));

    return vec_at_unchecked(vec, 0);
}

void* vec_front_mut(const Vec* const vec) {
    assert(!vec_is_empty(vec));

    return vec_at_mut_unchecked(vec, 0);
}

const void* vec_back(const Vec* const vec) {
    assert(!vec_is_empty(vec));

    return vec_at_unchecked(vec, vec->len - 1);
}

void* vec_back_mut(const Vec* const vec) {
    assert(!vec_is_empty(vec));

    return vec_at_mut_unchecked(vec, vec->len - 1);
}

const void* vec_at(const Vec* const vec, const size_t i) {
    assert(i < vec->len);

    return vec_at_unchecked(vec, i);
}

void* vec_at_mut(const Vec* const vec, const size_t i) {
    assert(i < vec->len);

    return vec_at_mut_unchecked(vec, i);
}

void vec_push_back(Vec* const vec, const void* const value) {
    if (vec->len == vec->cap) {
        vec->cap *= 2;
        vec->data = my_realloc(vec->data, vec->elem_size * vec->cap);
    }

    memcpy(vec_at_mut_unchecked(vec, vec->len), value, vec->elem_size);
    ++vec->len;
}

void vec_pop_back(Vec* const vec) {
    assert(!vec_is_empty(vec));

    --vec->len;
}
