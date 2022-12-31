//Too Many Things to Buy
#include <stdio.h>
#include <stdlib.h>

typedef struct _B
{
    int first, second, comp;
} B;

B arr[100005];
int cmp(const void *L, const void *R)
{
    B l = *((B *)L), r = *((B *)R);
    return l.comp - r.comp;
}
int main()
{
    int n, k;
    long long int ans = 0;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i].first);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i].second);
        arr[i].comp = arr[i].first - arr[i].second;
    }
    qsort(arr, n, sizeof(B), cmp);
    for (int i = 0; i < k; i++)
        ans += arr[i].first;
    for (int i = k; i < n; i++)
    {
        if (arr[i].comp < 0)
            ans += arr[i].first;
        else
            ans += arr[i].second;
    }
    printf("%lld\n", ans);
    return 0;
}