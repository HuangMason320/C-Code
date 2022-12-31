// problem 3 -> Progression
#include <stdio.h>
int main()
{
    int a, b, c, d, e;
    scanf("%d %d %d", &a, &b, &c);
    d = b - a;
    e = c - b;
    if (e == d)
    {
        printf("%d %d\n", a - d, c + d);
    }
    else
    {
        d = b / a;
        printf("%d %d\n", a / d, c * d);
    }

    return 0;
}