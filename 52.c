#include<stdio.h>
int cal(int n)
{
    int num=0;
    while(n)
    {
        if(n%10==1)
        {
            num++;
        }
        n=n/10;
    }
    return num;
}
int arr[1000001];
int main()
{
    for(int i=1;i<=1000000;i++)
    {
        arr[i]=arr[i-1]+cal(i);
    }
    int t;
    int a,b;
    int ans;
    scanf("%d",&t);
    for(int i=0;i<t;i++)
    {
        scanf("%d %d",&a,&b);
        ans=arr[b]-arr[a-1];
        printf("%d\n",ans);
    }
    return 0;
}
