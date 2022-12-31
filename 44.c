#include<stdio.h>
int max(int a,int b)
{
    if(a>b)     return a;
    else    return b;
}
int min(int a,int b)
{
    if(a<b)     return a;
    else    return b;
}
int main (void)
{
    int t;
    int n,m,k;
    int ans,temp;
    scanf("%d",&t);
    for(t;t>0;t--)
    {
        ans=0;
        long long int arr[5001]={0};
        scanf("%d %d %d", &n, &m, &k);
        
        for(int i=0;i<n;i++)
        {
            scanf("%lld",&arr[i]);
        }
        if(k>m)
        {
            k=m-1;
        }
        for(int j=0;j<=k;j++)
        {
            temp = 1e9+1;
            for(int h = 0; h<=m-k-1; h++)
            {
                temp = min(max(arr[j+h], arr[n-m+j+h]), temp);
            }
            ans = max(ans, temp);
        }
        printf("%d\n", ans);
    }
    return 0;
}