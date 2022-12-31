#include <stdio.h>
#include <string.h>

char a[1050];
char b[1050];

int main()
{
    scanf("%s %s",a,b);
    int len=strlen(a);
    if(pa(len,a,b))
    {
        printf("YES\n");
    }
    else    printf("NO\n");
}

int pa(int l,char a[l],char b[l])
{
    if(l%2==1)
    {
        for(int i=0;i<l;i++)
        {
            if(a[i]!=b[i])
            {
                return 0;
                break;
            }
            else if(i==l-1)
            {
                return 1;
            }
        }
    }
    else
    {
        //int temp=1;
        for(int i=0;i<l;i++)
        {
            if(a[i]!=b[i])
            {
                break;
            }
            else if(i==l-1)
            {
                return 1;
            }
        }
        l=l/2;
        char c[l+1],d[l+1],e[l+1],f[l+1];
        for(int i=0;i<l;i++)
        {
            c[i]=a[i];
            d[i]=a[l+i];
            e[i]=b[i];
            f[i]=b[l+i];
        }
        c[l]=d[l]=e[l]=f[l]='\0';
        return pa(l,c,f)&&pa(l,d,e);
    }
}