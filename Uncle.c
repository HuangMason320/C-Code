#include <stdio.h>

int pw(long long int x, long long int y, long long int m)
{
    long long temp = 1 % m;
    while (y)
    {
        if (y % 2 == 1)
        {
            temp = (temp * x) % m;
        }
        x = (x * x) % m;
        y /= 2;
    }
    return temp;
}
int main()
{
    long long int x, y, m;
    scanf("%lld %lld %lld", &x, &y, &m);
    printf("%d", pw(x % m, y, m));
}