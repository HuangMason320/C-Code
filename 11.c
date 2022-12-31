// Change the Cap
#include <stdio.h>
int forfree(int k)
{
    int r, q, sum = 0;
    while (k >= 3)
    {
        r = k % 3;     // 1//2//0
        q = k / 3;     // 4//1//1
        k = r + q;     // 5//3//1
        sum = sum + q; // 4//5//6
    }
    return sum;
}
int main()
{
    int n, free, start, k;
    scanf("%d", &n);
    free = forfree(n);
    start = n - free;
    for (int i = start; i <= n; i++)
    {
        k = forfree(i);
        if (i + k >= n)
        {
            printf("%d", i);
            break;
        }
    }
}