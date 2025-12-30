#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

float min_len = FLT_MAX;

float get_dist(float *pts, int i, int j)
{
    float dx = pts[2 * i] - pts[2 * j];
    float dy = pts[2 * i + 1] - pts[2 * j + 1];
    return sqrtf(dx * dx + dy * dy);
}

void solve(float *pts, int *p, int n, int k)
{
    if (k == n)
    {
        float d = 0;
        for (int i = 0; i < n; i++)
            d += get_dist(pts, p[i], p[(i + 1) % n]);
        if (d < min_len)
            min_len = d;
        return;
    }
    for (int i = k; i < n; i++)
    {
        int t = p[k]; p[k] = p[i]; p[i] = t;
        solve(pts, p, n, k + 1);
        t = p[k]; p[k] = p[i]; p[i] = t;
    }
}

int main(void)
{
    int n = 0, cap = 0, *p = NULL;
    float *pts = NULL, x, y;

    while (fscanf(stdin, "%f, %f", &x, &y) == 2)
    {
        if (n == cap)
        {
            cap = cap ? cap * 2 : 16;
            pts = realloc(pts, sizeof(float) * 2 * cap);
        }
        pts[2 * n] = x;
        pts[2 * n + 1] = y;
        n++;
    }

    if (n > 0)
    {
        p = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
            p[i] = i;
        solve(pts, p, n, 0);
        free(p);
    }
    else
        min_len = 0.0f;

    fprintf(stdout, "%.2f\n", min_len);
    free(pts);
    return 0;
}