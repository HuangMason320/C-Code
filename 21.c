#include <stdio.h>
int seq[200002];
int move[100002];

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int t=m;
    for(m;m>0;m--)
    {
        scanf("%d",&move[m]);//倒序
    }
    for(int i=1;i<=t;i++)
    {
        if(seq[move[i]]==0)
        {
            printf("%d\n",move[i]);
            seq[move[i]]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(seq[i]==0)
        {
            printf("%d\n",i);
        }
    }
}