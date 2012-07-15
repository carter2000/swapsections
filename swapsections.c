#include <stdio.h>

static int g_swapcount = 0;

void _swap(int* left, int* right)
{
    int temp = *left;
    *left = *right;
    *right = temp;
    ++g_swapcount;
}

void _reverse(int* datas, int start, int end)
{
    int i = start;
    int j = end - 1;
    while (i < j) {
        _swap(&datas[i], &datas[j]);
        ++i;
        --j;
    }
}

void reverseswap(int* datas, int sep, int len)
{
    _reverse(datas, 0, sep);
    _reverse(datas, sep, len);
    _reverse(datas, 0, len);
}

void _successiveswap(int* datas, int start, int end, int sep)
{
    int frontlen = sep - start;
    int backlen = end - sep;
    int i = 0;

    if (frontlen <= 0 || backlen <= 0) {
        return;
    }

    for (i = 0; i < backlen && i < frontlen; ++i) {
        _swap(&datas[i + start], &datas[i + sep]);
    }

    if (frontlen > backlen) {
        _successiveswap(datas, start + backlen, end, sep);
    } else {
        _successiveswap(datas, sep, end, sep + frontlen);
    }
}

void successiveswap(int* datas, int sep, int len)
{
    _successiveswap(datas, 0, len, sep);
}

void modswap(int* datas, int sep, int len)
{
    int temp = datas[0];
    int i = sep;
    int pre = 0;
    int next = i % len;
    while (next != 0) {
        datas[pre] = datas[next];
        ++g_swapcount;
        i += sep;
        pre = next;
        next = i % len;
    }
    datas[pre] = temp;
    ++g_swapcount;
}

int main()
{
    int i = 0;
    int datas[] = { 89, 3, 6, 2, 4, 7, 8, 23, 4, 34 };
    int results[] = { 23, 4, 34, 89, 3, 6, 2, 4, 7, 8 };
    int len = sizeof(datas) / sizeof(int);
    int sep = 7;

    //reverseswap(datas, sep, len);
    //successiveswap(datas, sep, len);
    modswap(datas, sep, len);

    printf("Swap-count: %d\n", g_swapcount);
    for (i = 0; i < len; ++i) {
        if (datas[i] != results[i]) {
            printf("error: (datas[%d]=%d) != (results[%d]=%d)\n", i, datas[i], i, results[i]);
            break;
        }
    }
    if (i == len) {
        printf("Succeed!\n");
    }

    return 0;
}
