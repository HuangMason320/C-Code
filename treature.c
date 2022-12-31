//ver 2
#include <stdio.h>
#include <stdlib.h>
#define MOD (int)(1e9+7)
//long long int MOD = 1e9 + 7;
long long int arr[1000005], pre[1000005];
int num;
int main()
{
    int n,q;
    int state = 1;
    scanf("%d %d", &n, &q);
    pre[0] = 1;
    for (int i = 0; i < n;i++)
    {
        scanf("%lld", &arr[i]);
        if (arr[i] < 0 && state != -1)
            state = -1;
        else if(arr[i]==0)
            state = 0;
        if(state==1)
        {
            pre[i + 1] = (pre[i] * arr[i]) % MOD;
        }
        else if(state==-1)
        {
            if(arr[i-1]<0)
            {
                pre[i + 1] = ((pre[i - 1] * arr[i]) % MOD * arr[i - 1]) % MOD;
            }
            else
                pre[i + 1] = pre[i];
        }
        else if (state == 0)
        {
            pre[i + 1] = pre[i];
        }
    }
    for (int i = 0; i < q; i++)
    {
        scanf("%d", &num);
        printf("%lld\n", pre[num]);
    }
    return 0;
}