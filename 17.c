// Money Money
#include <stdio.h>
int main()
{
    int a, b, c, total;
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    total = (x + y + z) / 2;
    c = total - x;
    a = total - y;
    b = total - z;
    printf("%d %d %d\n", a, b, c);
    return 0;
}