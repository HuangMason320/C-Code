#include<stdio.h>
#include<string.h>
#include<math.h>
int slove(int a,int b)//找公因數數量
{
    int ans;
    int i,flaga=0,flagb=0;
    int suma=0,sumb=0;
    for(i=1;i<=sqrt(a);i++)//第一個數字
    {
        flaga=0;
        if(i*i==a)
        {
            suma++;
            flaga=1;
        }
        if(flaga==0&&a%i==0)
        {
            suma+=2;
        }
    }
    for(i=1;i<=sqrt(b);i++)//第二個數字
    {
        flagb=0;
        if(i*i==b)
        {
            sumb++;
            flagb=1;
        }
        if(flagb==0&&b%i==0)
        {
            sumb+=2;
        }
    }
    if(suma<sumb)
    {
        ans=b;
        return ans;
    }
    else
    {
        ans=a;
        return ans;
    }
}
int main()
{
    int a,b,times,i;
    scanf("%d",&times);
    for(i=0;i<times;i++)
    {
        scanf("%d %d",&a,&b);
        if(b%2==0)
        {
            if (a==b)
            {
                printf("%d\n",b);
            }
            else if(b-2>=a)
            {
                a=b-2;
                printf("%d\n",slove(a,b));
                //break;
            }
            else
            {
                printf("%d\n",b);
                //break;
            }
        }
        else
        {
           if (a==b)
            {
                printf("%d\n",b);
            }
            else if(b-3>=a)
           {
               a=b-3;
               b=b-1;
                printf("%d\n",slove(a,b));
                //break;
           }
           else
           {
               printf("%d\n",b-1);
               //break;
           }
        }
    }
    return 0;
}
