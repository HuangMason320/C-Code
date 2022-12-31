#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double a[5005];
double pre[5005];

int main()
{
    double temp; 
    double ans = 0;
    int n,k;
    
    scanf("%d %d",&n,&k);

    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &a[i]);
        pre[i] = pre[i - 1] + a[i];
    }

    for (int j = n; j >= k; j--)
    {
        for (int i = 1; i <= n - j + 1; i++)
        {
            temp =(pre[j+i-1]-pre[i-1]) / j;
            if (temp > ans)
                ans = temp;
        }
    }
    printf("%.3lf\n ", ans);
}