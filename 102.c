#include <stdio.h>
#include <stdlib.h>

int arr[100005];
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int LowerBound(int num, int lft, int rgt)
{
    int mid;
    while (lft < rgt)
    {
        mid = (lft + rgt) / 2;
        if (num <= arr[mid])
        {
            rgt = mid;
        }
        else
            lft = mid + 1;
    }
    return rgt;
}
int UpperBound(int num, int lft, int rgt)
{
    int mid;
    while (lft < rgt)
    {
        mid = (lft + rgt) / 2;
        if (num < arr[mid])
        {
            rgt = mid;
        }
        else
            lft = mid + 1;
    }
    return rgt;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(int), cmp);
    int q, tmp, left, right;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        scanf("%d", &tmp);
        left = LowerBound(tmp, 0, n);
        right = UpperBound(tmp, 0, n);
        printf("%d\n", right - left);
    }
}