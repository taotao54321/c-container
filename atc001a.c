/**
 * AtCoder Typical Contest 001 A - 深さ優先探索
 *
 * https://atcoder.jp/contests/atc001/tasks/dfs_a
 */

#include <stdbool.h>
#include <stdio.h>

// ----- ここに vec.h, vec.c を貼る -----

// --------------------------------------

typedef struct Point {
    int y;
    int x;
} Point;

bool dfs(const int h, const int w, const Vec* const grid, const int sy, const int sx, const int gy, const int gx) {
    const int DY[4] = { -1, 0, 0, 1 };
    const int DX[4] = { 0, -1, 1, 0 };

    Vec* const stk = vec_with_capacity(sizeof(Point), 1024);
    {
        const Point start = { .y = sy, .x = sx };
        const int idx_start = w * sy + sx;
        vec_push_back(stk, &start);
        *(char*)vec_at_mut(grid, idx_start) = '#';
    }

    bool res = false;
    while (!vec_is_empty(stk)) {
        const Point cur = *(Point*)vec_back(stk);
        vec_pop_back(stk);

        if (cur.y == gy && cur.x == gx) {
            res = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            const Point to = {
                .y = cur.y + DY[i],
                .x = cur.x + DX[i],
            };
            if (to.y < 0 || h <= to.y || to.x < 0 || w <= to.x) continue;
            const int idx_to = w * to.y + to.x;
            if (*(char*)vec_at(grid, idx_to) == '#') continue;

            vec_push_back(stk, &to);
            *(char*)vec_at_mut(grid, idx_to) = '#';
        }
    }

    vec_delete(stk);

    return res;
}

int main(void) {
    int h, w;
    scanf("%d %d", &h, &w);

    const char ch_ini = '\0';
    Vec* const grid = vec_new(sizeof(char), h * w, &ch_ini);

    int sy = -1;
    int sx = -1;
    int gy = -1;
    int gx = -1;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char ch;
            scanf(" %c", &ch);
            switch (ch) {
            case 's':
                sy = y;
                sx = x;
                break;
            case 'g':
                gy = y;
                gx = x;
                break;
            }

            const int idx = w * y + x;
            *(char*)(vec_at_mut(grid, idx)) = ch;
        }
    }

    const bool ans = dfs(h, w, grid, sy, sx, gy, gx);
    puts(ans ? "Yes" : "No");

    vec_delete(grid);

    return 0;
}
