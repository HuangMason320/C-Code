#include<stdio.h>

int main()
{
    int t;
    int r,g,b;
    int s,l,m;
    int sum=0;
    scanf("%d",&t);
    for(int i=0;i<t;i++)
    {   
        sum=0;
        scanf("%d %d %d",&r,&g,&b);
        
        if(g>=r)
        {
            if(g>=b)
            {
                if(b>=r)
                {
                    s=r;
                    m=b;
                }
                else
                {
                    s=b;
                    m=r;
                }
                l=g;
            }
        } 
        if(b>=r)
        {
            if(b>=g)
            {
                if(g>=r)
                {
                    s=r;
                    m=g;
                }
                else
                {
                    s=g;
                    m=r;
                }
                l=b;
            }
        } 
        if(r>=g)
        {
            if(r>=b)
            {
                if(g>=b)
                {
                    s=b;
                    m=g;
                }
                else
                {
                    s=g;
                    m=b;
                }
                l=r;
            }

        }
        if(l>s+m)
        {
            printf("%d\n",s+m);
        }
        else
        {
            sum=(m+l-s)/2+s;
            printf("%d\n",sum);
        }
    }
    return 0;
}