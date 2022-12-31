#include <stdio.h>

int main()
{
    int l=0,r=0;
    int n;
    scanf("%d",&n);
    char s[100000+1];
    scanf("%s",s);
    for(int i=0;i<n;i++)
    {
        if(s[i]=='L')
        {
            l++;
        }
        else
        {
            r++;
        }
    }
    printf("%d\n",l+r+1);
}