#include <stdio.h>
#include <stdlib.h>
int a[20];
int n;
int k;
int ans=0;
int num(int ,int );

int main()
{
    scanf( "%d %d", &n, &k);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    ans=num(0,0);
    printf("%d\n",ans);
}
int num(int id,int sum)
{
    if(sum == k)  return 1;
    if(id >= n || sum > k)    return 0;
    return num(id+1,sum+a[id]) + num(id+1,sum);
}