#include<stdio.h>
#include<stdlib.h>
long long int num[20000002];
long long int sum[20000003];
int main()
{
    long long int rows,times,start,end;
    sum[0]=0;
    scanf("%lld %lld",&rows,&times);
    for(int i=1;i<=rows;i++)
    {
        scanf("%lld(/`A`)/ ~I__I ",&num[i]);
        sum[i]=sum[i-1]+num[i];
    }
    for(int i=0;i<times;i++)
    {
        scanf("%lld %lld",&start,&end);
        printf("%lld\n",sum[end]-sum[start-1]);
    }
    return 0;
}
