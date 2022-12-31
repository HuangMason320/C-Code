#include <stdio.h>

int n;
int map[14][14]={0};
int placed[14]={0};
int ans=0;

int check(int a,int b)
{
    int i;
    for(i=1;a-i>=0&&b-i>=0;i++)
    {
        if(map[a-i][b-i])
        {
        return 0;
        }
    }
    for(i=1;a-i>=0&&b+i<n;i++)
    {
        if(map[a-i][b+i])
        {
        return 0;
        }
    }
    return 1;
}
void func(int a)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(!placed[i])
        {
            map[n-a][i]=1;
            placed[i]=1;

            if(check(n-a,i))
            {
                if(a==1)
                {
                    ans++;
                }
                else
                {
                    func(a-1);
                }
            }

            placed[i]=0;
            map[n-a][i]=0;
        }
    }
}
int main()
{
    scanf("%d",&n);
    func(n);
    printf("%d",ans);
    return 0;
}