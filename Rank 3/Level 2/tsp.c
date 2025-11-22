#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
    float x;
    float y;
} Point;

float distance(Point a, Point b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

float path_length(Point *cities, int *perm, int n) {
    float len = 0.0f;
    int i;
    for (i = 0; i < n; i++) {
        Point p1 = cities[perm[i]];
        Point p2 = cities[perm[(i + 1) % n]]; // wrap around
        len += distance(p1, p2);
    }
    return len;
}

void permute(Point *cities, int *perm, int l, int r, float *min_len) {
    int i;
    if (l == r) {
        float len = path_length(cities, perm, r + 1);
        if (len < *min_len)
            *min_len = len;
        return;
    }
    for (i = l; i <= r; i++) {
        swap(&perm[l], &perm[i]);
        permute(cities, perm, l + 1, r, min_len);
        swap(&perm[l], &perm[i]);
    }
}

int main(void) {
    Point *cities = NULL;
    int capacity = 10, n = 0;
    cities = (Point *)malloc(sizeof(Point) * capacity);
    if (!cities)
        return 1;

    while (1) {
        if (n >= capacity) {
            capacity *= 2;
            Point *tmp = (Point *)realloc(cities, sizeof(Point) * capacity);
            if (!tmp) {
                free(cities);
                return 1;
            }
            cities = tmp;
        }
        int res = fscanf(stdin, "%f, %f\n", &cities[n].x, &cities[n].y);
        if (res != 2)
            break;
        n++;
    }

    if (n == 0) {
        write(1, "0.00\n", 5);
        free(cities);
        return 0;
    }

    int *perm = (int *)malloc(sizeof(int) * n);
    if (!perm) {
        free(cities);
        return 1;
    }
    int i;
    for (i = 0; i < n; i++)
        perm[i] = i;

    float min_len = FLT_MAX;
    permute(cities, perm, 0, n - 1, &min_len);

    char buffer[32];
    int len = snprintf(buffer, sizeof(buffer), "%.2f\n", min_len);
    write(1, buffer, len);

    free(cities);
    free(perm);
    return 0;
}
