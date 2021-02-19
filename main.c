#include <assert.h>

#include "deque.h"
#include "vec.h"

static void test_vec_new(void) {
    {
        Vec* const vec = vec_new(sizeof(int), 0, NULL);
        assert(vec_is_empty(vec));
        assert(vec_len(vec) == 0);
        assert(vec_capacity(vec) > 0);
        vec_delete(vec);
    }
    {
        const size_t len = 42;
        const int value = 10;
        Vec* const vec = vec_new(sizeof(int), len, &value);
        assert(!vec_is_empty(vec));
        assert(vec_len(vec) == len);
        assert(vec_capacity(vec) >= len);
        for (size_t i = 0; i < len; ++i)
            assert(*(int*)vec_at(vec, i) == value);
        vec_delete(vec);
    }
}

static void test_vec_with_capacity(void) {
    {
        Vec* const vec = vec_with_capacity(sizeof(int), 0);
        assert(vec_is_empty(vec));
        assert(vec_len(vec) == 0);
        assert(vec_capacity(vec) > 0);
        vec_delete(vec);
    }
    {
        const size_t cap = 42;
        Vec* const vec = vec_with_capacity(sizeof(int), cap);
        assert(vec_is_empty(vec));
        assert(vec_len(vec) == 0);
        assert(vec_capacity(vec) >= cap);
        vec_delete(vec);
    }
}

static void test_vec_operation(void) {
    const int value_ini = 10;
    Vec* const vec = vec_new(sizeof(int), 3, &value_ini);

    {
        int* const p = vec_data_mut(vec);
        p[1] = value_ini + 1;
        p[2] = value_ini + 2;
        assert(p[0] == value_ini);
        assert(p[1] == value_ini + 1);
        assert(p[2] == value_ini + 2);
    }

    *(int*)vec_front_mut(vec) = 15;
    assert(*(int*)vec_front(vec) == 15);

    *(int*)vec_back_mut(vec) = 25;
    assert(*(int*)vec_back(vec) == 25);

    *(int*)vec_at_mut(vec, 1) = 20;
    assert(*(int*)vec_at(vec, 1) == 20);

    {
        const int value = 30;
        vec_push_back(vec, &value);
    }
    {
        const int value = 35;
        vec_push_back(vec, &value);
    }
    vec_pop_back(vec);

    assert(vec_len(vec) == 4);
    assert(*(int*)vec_at(vec, 0) == 15);
    assert(*(int*)vec_at(vec, 1) == 20);
    assert(*(int*)vec_at(vec, 2) == 25);
    assert(*(int*)vec_at(vec, 3) == 30);

    vec_delete(vec);
}

static void test_deque_new(void) {
    {
        Deque* deq = deque_new(sizeof(int), 0, NULL);
        assert(deque_is_empty(deq));
        assert(deque_len(deq) == 0);
        assert(deque_capacity(deq) > 0);
        deque_delete(deq);
    }
    {
        const size_t len = 42;
        const int value = 10;
        Deque* const deq = deque_new(sizeof(int), len, &value);
        assert(!deque_is_empty(deq));
        assert(deque_len(deq) == len);
        assert(deque_capacity(deq) >= len);
        for (size_t i = 0; i < len; ++i)
            assert(*(int*)deque_at(deq, i) == value);
        deque_delete(deq);
    }
}

static void test_deque_with_capacity(void) {
    {
        Deque* const deq = deque_with_capacity(sizeof(int), 0);
        assert(deque_is_empty(deq));
        assert(deque_len(deq) == 0);
        assert(deque_capacity(deq) > 0);
        deque_delete(deq);
    }
    {
        const size_t cap = 42;
        Deque* const deq = deque_with_capacity(sizeof(int), cap);
        assert(deque_is_empty(deq));
        assert(deque_len(deq) == 0);
        assert(deque_capacity(deq) >= cap);
        deque_delete(deq);
    }
}

static void test_deque_operation(void) {
    const int value_ini = 10;
    Deque* const deq = deque_new(sizeof(int), 3, &value_ini);

    *(int*)deque_front_mut(deq) = 15;
    assert(*(int*)deque_front(deq) == 15);

    *(int*)deque_back_mut(deq) = 25;
    assert(*(int*)deque_back(deq) == 25);

    *(int*)deque_at_mut(deq, 1) = 20;
    assert(*(int*)deque_at(deq, 1) == 20);

    {
        const int value = 30;
        deque_push_back(deq, &value);
    }
    {
        const int value = 35;
        deque_push_back(deq, &value);
    }
    {
        const int value = 40;
        deque_push_back(deq, &value);
    }

    {
        const int value = 10;
        deque_push_front(deq, &value);
    }
    {
        const int value = 5;
        deque_push_front(deq, &value);
    }
    {
        const int value = 0;
        deque_push_front(deq, &value);
    }

    deque_pop_front(deq);
    deque_pop_back(deq);

    assert(deque_len(deq) == 7);
    assert(*(int*)deque_at(deq, 0) == 5);
    assert(*(int*)deque_at(deq, 1) == 10);
    assert(*(int*)deque_at(deq, 2) == 15);
    assert(*(int*)deque_at(deq, 3) == 20);
    assert(*(int*)deque_at(deq, 4) == 25);
    assert(*(int*)deque_at(deq, 5) == 30);
    assert(*(int*)deque_at(deq, 6) == 35);

    deque_delete(deq);
}

int main(void) {
    test_vec_new();
    test_vec_with_capacity();
    test_vec_operation();

    test_deque_new();
    test_deque_with_capacity();
    test_deque_operation();

    return 0;
}
