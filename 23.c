#include<stdio.h>
int a[200005]; //for watermelon
int b[200005];  //for the order
int ans[200005];

int main()
{
  int n;
  int z=0;
  int now=0;
  int last=0;
  scanf("%d",&n);
  for(int i=0;i<n;i++)//A array
  {
      scanf("%d",&a[i]);
  }
  for(int i=0;i<n;i++)//B array
  {
      scanf("%d",&b[i]);
  }
  for(int i=0;i<n;i++)
  {
      int x=b[i];
      int num=0;
      now=last;
      while(now<=n)
      {
            if(x==a[now])
            {
                ans[z]=num+1;
                z++;
                last=now+1;
                break;
            }
            else
            {
                if(now == n)
                {
                    ans[z]=0;
                    z++;
                    break;
                }
                else
                {
                    num++;
                    now++;
                }
            }
      }

    }
    for(int i=0;i<n-1;i++)
    {
        printf("%d ",ans[i]);

    }
    printf("%d\n",ans[n-1]);
    return 0;
}