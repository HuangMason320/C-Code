// Restaurants in Hsinchu
#include <stdio.h>
#define MOD (int)(1e9 + 7)

typedef struct
{
    long long m[3][3];
} matrix;

matrix a, e, zero;
long long int i;

matrix matmul(matrix x, matrix y)
{
    matrix c = zero;
    for (int z = 1; z < 3; z++)
    {
        for (int j = 1; j < 3; ++j)
        {
            for (int k = 1; k <= 2; ++k)
            {
                c.m[z][j] = ((x.m[z][k] % MOD * y.m[k][j] % MOD) % MOD + c.m[z][j]) % MOD;
            }
        }
    }
    return c;
}

matrix fpw(matrix a, long long int n)
{
    if (n == 0)
        return e;
    matrix temp;
    temp = fpw(a, n / 2);
    if (n % 2 == 1)
        return matmul(matmul(temp, temp), a);
    else
        return matmul(temp, temp);
}

int main()
{
    e.m[1][1] = 1;
    e.m[1][2] = 0;
    e.m[2][1] = 0;
    e.m[2][2] = 1;

    a.m[1][1] = 1;
    a.m[1][2] = 1;
    a.m[2][1] = 1;
    a.m[2][2] = 0;

    while (scanf("%lld", &i) != EOF)
    {
        if (i < 3)
            printf("1\n");
        else
        {
            matrix count = fpw(a, i - 2);
            long long ans = (count.m[1][1] + count.m[1][2]) % MOD;
            printf("%lld\n", ans);
        }
    }
}