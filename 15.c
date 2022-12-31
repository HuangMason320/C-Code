// Factor Counter
#include <stdio.h>
#include <stdlib.h>

int arr[20004];

int main()
{
    for (int i = 1; i < 20001; i++)
    {
        int temp = 1;
        while (temp * temp <= i)
        {
            temp += 1;
        }
        for (int j = 1; j <= temp; j++)
        {
            if (i % j == 0)
                arr[i]++;
        }
        if (i > 2)
        {
            arr[i]++;
        }
    }

    int t;
    scanf("%d", &t);
    for (t; t > 0; t--)
    {
        int a, b;
        int ans;
        scanf("%d %d", &a, &b);
        if (a == b)
        {
            printf("%d\n", a);
        }
        else
        {
            ans = 0;
            int compare = 0;
            for (int i = a; i <= b; i++)
            {
                if (arr[i] > compare)
                {
                    compare = arr[i];
                    ans = i;
                }
            }
            printf("%d\n", ans);
        }
    }
}