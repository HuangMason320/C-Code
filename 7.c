// Airplane Shooter
#include <stdio.h>
#include <stdlib.h>

typedef struct _A
{
    long long int admin, lin_num, idx;
} A;

A a[100002];

int cmp(const void *L, const void *R)
{
    A l = *((A *)L), r = *((A *)R);
    if (l.admin != r.admin)
        return l.admin - r.admin;
    else if (l.lin_num != r.lin_num)
        return l.lin_num - r.lin_num;
    else
        return l.idx - r.idx;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld %lld", &a[i].admin, &a[i].lin_num);
        a[i].idx = i + 1;
    }
    qsort(a, n, sizeof(A), cmp);
    for (int i = 0; i < n - 1; i++)
    {
        printf("%lld ", a[i].idx);
    }
    printf("%lld\n", a[n - 1].idx);
    return 0;
}