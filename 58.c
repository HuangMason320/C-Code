#include <stdio.h>
int v[10001];
int temp;
int main()
{
    int t;
    scanf("%d",&t);
    for(t;t>0;t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&v[i]);
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<i;j++)
            {
                if (v[j] > v[i]) 
                {
                    temp = v[j];
                    v[j] = v[i];
                    v[i] = temp;
                }
            }
        }

        for(int i=0;i<n;i++)
        {
          if(i==n-1)  printf("%d\n",v[i]);
          else  printf("%d ",v[i]);
        }
        //printf("%d\n",v[n-1]);
    }
}