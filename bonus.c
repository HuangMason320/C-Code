#include <stdio.h>
#include <string.h>
#define LEN 1001
char S[LEN];
char s[LEN];

int main()
{
    int ans[LEN]={0};
    scanf("%s %s",S,s);
    int sum=0;
    for(int i=0;i<strlen(S)-strlen(s)+1;i++)
    {
        ans[i]=sum;
        if(S[i]==s[0])
        {
            int temp = 1;
            for(int j=1;j<strlen(s);j++)
            {
                if(s[j]!=S[i+j])
                {
                    temp=0;
                    ans[i+j]=0;
                    break;
                }
            }
            if(temp)
            {
                sum++;
                ans[i]=sum;
            }
        }
    }
    int t;
    int l,r;
    scanf("%d",&t);
    for(t;t>0;t--)
    {
        scanf("%d %d",&l,&r);
        if(l-2>=0) printf("%d\n",ans[r-strlen(s)]-ans[l-2]);
        else printf("%d\n",ans[r-strlen(s)]);
    }
    return 0;
}