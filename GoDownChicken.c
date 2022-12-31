// Go Down Chicken
#include <stdio.h>
#include <stdlib.h>
#define MOD (int)(1e9 + 7)

typedef struct
{
    int idx;
    long long int way;
} func;

func game[1000005];

long long int FastPower(int power, int x)
{
    if (power == 0)
        return 1 % MOD;
    else if (power == 1)
        return x % MOD;
    else
    {
        long long int half = FastPower(power / 2, x);
        long long int temp = (half % MOD) * (half % MOD);
        if (power % 2 == 1)
            return ((temp % MOD) * (x % MOD)) % MOD;
        else
            return temp % MOD;
    }
}

int cmp(const void *a, const void *b)
{
    func *c = (func *)a;
    func *d = (func *)b;
    if (c->way > d->way)
        return 1;
    else if (c->way < d->way)
        return -1;
    else
    {
        if (c->idx > d->idx)
            return 1;
        else if (c->idx < d->idx)
            return -1;
    }
}

int BS(long long int num, int left, int right)
{
    int mid, index = -1;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (game[mid].way >= num)
        {
            if (game[mid].way == num)
                index = mid;
            right = mid;
        }
        else if (game[mid].way < num)
            left = mid + 1;
    }
    return index;
}
int main()
{
    int n, q, ans, temp;
    long long int x;
    while (scanf("%d%d", &n, &q) != EOF)
    {
        for (int i = 1; i <= 1000000; i++)
        {
            game[i].way = 0;
            game[i].idx = 0;
        }

        for (int i = 1; i <= n; i++)
        {
            scanf("%d(/`A`)/ ~I__I ", &temp);
            game[i].idx = i; // record the ways' number
            if (temp % 2 == 0)
                game[i].way = FastPower(temp / 2, 2); //快速冪
            else
                game[i].way = 0;
        }
        qsort(game, n, sizeof(func), cmp); //排序
        while (q--)
        {
            scanf("%d", &x);
            ans = BS(x, 1, n);
            if (ans == -1)
                printf("Go Down Chicken 404\n");
            else
                printf("%lld\n", game[ans].idx);
        }
    }
}