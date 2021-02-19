#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct Vec Vec;

// 要素サイズ elem_size, 長さ len の Vec を返す。
// Vec の容量は len 以上の正の値となる。
// 各要素は value で初期化される。len == 0 の場合のみ、value に NULL を渡してもよい。
Vec* vec_new(size_t elem_size, size_t len, const void* value);

// 容量 cap 以上の空 Vec を返す。
// cap に 0 を渡した場合、正のデフォルト容量の空 Vec を返す。
Vec* vec_with_capacity(size_t elem_size, size_t cap);

// vec を解放する。
void vec_delete(Vec* vec);

// vec を空にする。メモリは解放しない。
void vec_clear(Vec* vec);

// vec が空かどうかを返す。
bool vec_is_empty(const Vec* vec);

// vec の長さを返す。
size_t vec_len(const Vec* vec);

// vec の容量を返す。
size_t vec_capacity(const Vec* vec);

// vec の内部配列の先頭を指す const ポインタを返す。
const void* vec_data(const Vec* vec);

// vec の内部配列の先頭を指すポインタを返す。
void* vec_data_mut(const Vec* vec);

// vec の先頭要素への const ポインタを返す。
// vec が空の場合の動作は未定義。
const void* vec_front(const Vec* vec);

// vec の先頭要素へのポインタを返す。
// vec が空の場合の動作は未定義。
void* vec_front_mut(const Vec* vec);

// vec の末尾要素への const ポインタを返す。
// vec が空の場合の動作は未定義。
const void* vec_back(const Vec* vec);

// vec の末尾要素へのポインタを返す。
// vec が空の場合の動作は未定義。
void* vec_back_mut(const Vec* vec);

// vec の i 番目の要素への const ポインタを返す。
// i が範囲外の場合の動作は未定義。
const void* vec_at(const Vec* vec, size_t i);

// vec の i 番目の要素へのポインタを返す。
// i が範囲外の場合の動作は未定義。
void* vec_at_mut(const Vec* vec, size_t i);

// vec の末尾に value を追加する。
void vec_push_back(Vec* vec, const void* value);

// vec の末尾要素を削除する。
// vec が空の場合の動作は未定義。
void vec_pop_back(Vec* vec);
