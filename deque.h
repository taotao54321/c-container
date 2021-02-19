#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct Deque Deque;

// 要素サイズ elem_size, 長さ len の Deque を返す。
// Deque の容量は len 以上の正の値となる。
// 各要素は value で初期化される。len == 0 の場合のみ、value に NULL を渡してもよい。
Deque* deque_new(size_t elem_size, size_t len, const void* value);

// 容量 cap 以上の空 Deque を返す。
// cap に 0 を渡した場合、正のデフォルト容量の空 Deque を返す。
Deque* deque_with_capacity(size_t elem_size, size_t cap);

// deq を解放する。
void deque_delete(Deque* deq);

// deq を空にする。メモリは解放しない。
void deque_clear(Deque* deq);

// deq が空かどうかを返す。
bool deque_is_empty(const Deque* deq);

// deq の長さを返す。
size_t deque_len(const Deque* deq);

// deq の容量を返す。
size_t deque_capacity(const Deque* deq);

// deq の先頭要素への const ポインタを返す。
// deq が空の場合の動作は未定義。
const void* deque_front(const Deque* deq);

// deq の先頭要素へのポインタを返す。
// deq が空の場合の動作は未定義。
void* deque_front_mut(const Deque* deq);

// deq の末尾要素への const ポインタを返す。
// deq が空の場合の動作は未定義。
const void* deque_back(const Deque* deq);

// deq の末尾要素へのポインタを返す。
// deq が空の場合の動作は未定義。
void* deque_back_mut(const Deque* deq);

// deq の i 番目の要素への const ポインタを返す。
// i が範囲外の場合の動作は未定義。
const void* deque_at(const Deque* deq, size_t i);

// deq の i 番目の要素へのポインタを返す。
// i が範囲外の場合の動作は未定義。
void* deque_at_mut(const Deque* deq, size_t i);

// deq の先頭に value を追加する。
void deque_push_front(Deque* deq, const void* value);

// deq の末尾に value を追加する。
void deque_push_back(Deque* deq, const void* value);

// deq の先頭要素を削除する。
// deq が空の場合の動作は未定義。
void deque_pop_front(Deque* deq);

// deq の末尾要素を削除する。
// deq が空の場合の動作は未定義。
void deque_pop_back(Deque* deq);
