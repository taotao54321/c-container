/**
 * AtCoder Typical Context 002 A - 幅優先探索
 *
 * https://atcoder.jp/contests/atc002/tasks/abc007_3
 */

#include <stdbool.h>
#include <stdio.h>

// ----- ここに deque.h, deque.c を貼る -----

// ------------------------------------------

typedef struct Point {
    int y;
    int x;
    int d;
} Point;

int bfs(const int h, const int w, char* const grid, const int sy, const int sx, const int gy, const int gx) {
    const int DY[4] = { -1, 0, 0, 1 };
    const int DX[4] = { 0, -1, 1, 0 };

    Deque* const deq = deque_with_capacity(sizeof(Point), 1024);
    {
        const Point start = { .y = sy, .x = sx, .d = 0 };
        const int idx_start = w * sy + sx;
        deque_push_back(deq, &start);
        grid[idx_start] = '#';
    }

    int res = -1;
    while (!deque_is_empty(deq)) {
        const Point cur = *(Point*)deque_front(deq);
        deque_pop_front(deq);

        if (cur.y == gy && cur.x == gx) {
            res = cur.d;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            const Point to = {
                .y = cur.y + DY[i],
                .x = cur.x + DX[i],
                .d = cur.d + 1,
            };
            if (to.y < 0 || h <= to.y || to.x < 0 || w <= to.x) continue;
            const int idx_to = w * to.y + to.x;
            if (grid[idx_to] == '#') continue;

            deque_push_back(deq, &to);
            grid[idx_to] = '#';
        }
    }

    deque_delete(deq);

    return res;
}

int main(void) {
    int h, w;
    scanf("%d %d", &h, &w);

    int sy, sx;
    scanf("%d %d", &sy, &sx);
    --sy;
    --sx;

    int gy, gx;
    scanf("%d %d", &gy, &gx);
    --gy;
    --gx;

    static char grid[500 * 500];

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char ch;
            scanf(" %c", &ch);

            const int idx = w * y + x;
            grid[idx] = ch;
        }
    }

    const int ans = bfs(h, w, grid, sy, sx, gy, gx);
    printf("%d\n", ans);

    return 0;
}
