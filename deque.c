#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"

static void rpanic(void) { abort(); }

static void* my_malloc(const size_t size) {
    void* const res = malloc(size);
    if (!res) rpanic();
    return res;
}

// リングバッファによる実装。
// 長さ cap+1 のバッファを使う。
// head は Deque の先頭要素の内部インデックス。
// tail は Deque の末尾の次の要素の内部インデックス。
// head と tail が一致するとき、Deque は空。
// tail の次が head であるとき、Deque は満杯。
struct Deque {
    size_t elem_size;
    size_t head;
    size_t tail;
    size_t cap;
    void* data;
};

// 内部インデックス i_in の前の内部インデックスを返す。
static size_t deque_prev(const Deque* const deq, const size_t i_in) {
    return i_in == 0 ? deq->cap : i_in - 1;
}

// 内部インデックス i_in の次の内部インデックスを返す。
static size_t deque_next(const Deque* const deq, const size_t i_in) {
    return i_in == deq->cap ? 0 : i_in + 1;
}

// 外部インデックス i_ex に対応する内部インデックスを返す。
static size_t deque_idx_internal(const Deque* const deq, const size_t i_ex) {
    const size_t k = deq->cap - deq->head;
    return i_ex <= k ? deq->head + i_ex : i_ex - k - 1;
}

static bool deque_is_full(const Deque* const deq) {
    return deque_next(deq, deq->tail) == deq->head;
}

static const void* deque_at_unchecked(const Deque* const deq, const size_t i) {
    return (char*)deq->data + deq->elem_size * deque_idx_internal(deq, i);
}

static void* deque_at_mut_unchecked(const Deque* const deq, const size_t i) {
    return (char*)deq->data + deq->elem_size * deque_idx_internal(deq, i);
}

static void deque_grow(Deque* const deq) {
    const size_t len = deque_len(deq);

    const size_t cap_new = 2 * deq->cap;
    void* data_new = my_malloc(deq->elem_size * (cap_new + 1));

    for (size_t i = 0; i < len; ++i) {
        void* dst = (char*)data_new + deq->elem_size * i;
        memcpy(dst, deque_at_unchecked(deq, i), deq->elem_size);
    }

    free(deq->data);

    deq->head = 0;
    deq->tail = len;
    deq->cap = cap_new;
    deq->data = data_new;
}

Deque* deque_new(const size_t elem_size, const size_t len, const void* const value) {
    const size_t cap = len == 0 ? 1 : len;

    Deque* deq = deque_with_capacity(elem_size, cap);
    deq->tail = len;

    for (size_t i = 0; i < len; ++i)
        memcpy(deque_at_mut_unchecked(deq, i), value, elem_size);

    return deq;
}

Deque* deque_with_capacity(const size_t elem_size, size_t cap) {
    if (cap == 0) cap = 1;

    Deque* deq = (Deque*)my_malloc(sizeof(Deque));
    deq->elem_size = elem_size;
    deq->head = deq->tail = 0;
    deq->cap = cap;
    deq->data = my_malloc(elem_size * (cap + 1));

    return deq;
}

void deque_delete(Deque* const deq) {
    free(deq->data);

    deq->elem_size = 0;
    deq->head = deq->tail = 0;
    deq->cap = 0;
    deq->data = NULL;

    free(deq);
}

bool deque_is_empty(const Deque* const deq) {
    return deq->head == deq->tail;
}

size_t deque_len(const Deque* const deq) {
    const size_t cap = deq->cap;
    const size_t head = deq->head;
    const size_t tail = deq->tail;
    return head <= tail ? tail - head : cap + 1 - (head - tail);
}

size_t deque_capacity(const Deque* const deq) {
    return deq->cap;
}

const void* deque_front(const Deque* const deq) {
    assert(!deque_is_empty(deq));

    return deque_at_unchecked(deq, 0);
}

void* deque_front_mut(const Deque* const deq) {
    assert(!deque_is_empty(deq));

    return deque_at_mut_unchecked(deq, 0);
}

const void* deque_back(const Deque* const deq) {
    assert(!deque_is_empty(deq));

    return deque_at_unchecked(deq, deque_len(deq) - 1);
}

void* deque_back_mut(const Deque* const deq) {
    assert(!deque_is_empty(deq));

    return deque_at_mut_unchecked(deq, deque_len(deq) - 1);
}

const void* deque_at(const Deque* const deq, const size_t i) {
    assert(i < deque_len(deq));

    return deque_at_unchecked(deq, i);
}

void* deque_at_mut(const Deque* const deq, const size_t i) {
    assert(i < deque_len(deq));

    return deque_at_mut_unchecked(deq, i);
}

void deque_push_front(Deque* const deq, const void* const value) {
    if (deque_is_full(deq))
        deque_grow(deq);
    assert(!deque_is_full(deq));

    deq->head = deque_prev(deq, deq->head);
    void* dst = (char*)deq->data + deq->elem_size * deq->head;
    memcpy(dst, value, deq->elem_size);
}

void deque_push_back(Deque* const deq, const void* const value) {
    if (deque_is_full(deq))
        deque_grow(deq);
    assert(!deque_is_full(deq));

    void* dst = (char*)deq->data + deq->elem_size * deq->tail;
    memcpy(dst, value, deq->elem_size);
    deq->tail = deque_next(deq, deq->tail);
}

void deque_pop_front(Deque* const deq) {
    assert(!deque_is_empty(deq));

    deq->head = deque_next(deq, deq->head);
}

void deque_pop_back(Deque* const deq) {
    assert(!deque_is_empty(deq));

    deq->tail = deque_prev(deq, deq->tail);
}
