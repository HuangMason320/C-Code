#include <stdio.h>

long long int arr[1000001];
int n,k,q;

int BS( long long int find, long long int l,long long int r){
   if(l>r) return -1;
   int m=(l+r)/2;
   if(arr[m]>=find)
   {
       if(m==0||arr[m-1]<find||m==n-k) return m+1;
       else return BS(find,l,m-1);
   }
   else return BS(find,m+1,r);
}

int main()
{
    long long int f;

    scanf("%d %d %d",&n,&k,&q);

    for(int i=0;i<k;i++)
    {
        scanf("%lld",&arr[n-k+i]);
    }
    for(int i=k;i<n;i++)
    {
        scanf("%lld",&arr[i-k]);
    }

    while(q--)
    {
        scanf("%lld",&f);
        if(arr[n-k-1]<f)
        {
            printf("gan ni nya sai bau\n");
        }
        else
        {
            int ans1=BS(f,0,n-k-1);
            long long int check1=arr[ans1-1]-f;
            int ans2=BS(f,n-k,n-1);
            long long int check2=arr[ans2-1]-f;
            if(ans1==-1)
            {
                printf("%lld\n",ans2);
            }
            else if(ans2==-1)
            {
                printf("%lld\n",ans1);
            }
            else
            {
                if(check1>check2)
                {
                    printf("%lld\n",ans2);
                }
                else
                {
                    printf("%lld\n",ans1);
                }
            }
        }
    }
}
