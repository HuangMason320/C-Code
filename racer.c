#include <stdio.h>

long long int arr[100001];

int main()
{
    int n,k;
    int stat=1;
    long long int pos=0,ans=0;
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&arr[i]);
    }
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            if(k<arr[i])
            {
                i=n;
                stat=0;
            }
        }
        else if(arr[i]+k<arr[i+1])
        {
            i=n;
            stat=0;
        }
        else
        {
            if(pos+k<arr[i])
            {
                pos=arr[i-1];
                ans++;
            }
        }
    }
    if(stat==0) printf("The Legend Falls.\n");
    else    printf("%lld\n", ans);
    return 0;
}
