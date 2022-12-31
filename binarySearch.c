// Lucky Ghoul Dawn baby(HW5)
#include <stdio.h>

int Bs(int *arr, long long int num, int left, int right)
{
    if (num > arr[right] || num < arr[left])
        return -1;
    int mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (arr[mid] > num)
            right = mid - 1;
        else if (arr[mid] < num)
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

int main()
{
    int n, q, arr[2000005], ans;
    long long int a;
    while (~scanf("%d %d", &n, &q))
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &arr[i]);
        }
        while (q--)
        {
            scanf("%lld", &a);
            ans = Bs(arr, a, 1, n);
            if (ans == -1)
                printf("Break your bridge!\n");
            else
                printf("%d\n", ans);
        }
    }
    return 0;
}