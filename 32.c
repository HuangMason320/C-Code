#include <stdio.h>

int func(int a,int b)
{
    if(b==0)    return a;
    else    return func(b,a%b);
}

int main()
{
    int n;
    int temp;
    int ans=0;
    int a[1000];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            temp=func(a[i],a[j]);
            //printf("%d\n",temp);
            if(temp>ans)
            {
                ans=temp;
            }
        }
    }
    printf("%d\n",ans);
}