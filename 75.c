//Thanos' Dilemma
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct mat{
    long long int matrix[5][5];
} mat;

mat zero, identity;
long long int mod=1e9+7;

mat multi(mat a,mat b)
{
    mat product = zero;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            for (int k = 1; k <= 3; k++)
            {
                product.matrix[i][j] = (product.matrix[i][j] + ((a.matrix[i][k] % mod) * (b.matrix[k][j] % mod)) % mod) % mod;
            }
        }
    }
    return product;
}

mat fpw(mat x, long long int y)
{
    if (y == 0)
        return identity;
    mat tmp;
    tmp = fpw(x, y / 2);
    if (y % 2 == 0)
        return multi(tmp, tmp);
    else
        return multi(multi(tmp, tmp), x);
}

int main()
{
    int t;
    long long int x;
    
    mat first;
    first.matrix[1][1] = 13;
    first.matrix[2][1] = 12;
    first.matrix[3][1] = 1;

    mat a;
    a.matrix[1][1]=1;
    a.matrix[1][2]=2;
    a.matrix[1][3]=1;
    a.matrix[2][1]=1;
    a.matrix[2][2]=0;
    a.matrix[2][3]=0;
    a.matrix[3][1]=0;
    a.matrix[3][2]=1;
    a.matrix[3][3]=0;

    identity.matrix[1][1]=1;
    identity.matrix[1][2]=0;
    identity.matrix[1][3]=0;
    identity.matrix[2][1]=0;
    identity.matrix[2][2]=1;
    identity.matrix[2][3]=0;
    identity.matrix[3][1]=0;
    identity.matrix[3][2]=0;
    identity.matrix[3][3]=1;

    scanf("%d", &t);
    for (t; t > 0; t--)
    {
        scanf("%lld", &x);
        if(x==1)
        {
            printf("%lld\n", first.matrix[3][1]);
            continue;
        }
        if(x==2)
            {
                printf("%lld\n", first.matrix[2][1]);
                continue;
            }
        if(x==3)
        {
            printf("%lld\n", first.matrix[1][1]);
            continue;
        }
        else
        {
            mat left_mat=fpw(a, x-3);
            long long int ans=0;
            for (int i = 1; i <= 3;i++)
            {
                ans = (ans + left_mat.matrix[1][i] % mod * first.matrix[i][1] % mod) % mod;
            }
            if(ans<0)
                ans = ans + mod;
            printf("%lld\n", ans);
        }
    }
}