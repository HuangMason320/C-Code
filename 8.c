#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    char B[9];
    char A[5];
    char sub[5];
    scanf("%s",A);
    int alen=strlen(A);
    scanf("%d",&n);
    int ans=0;
    for(n;n>0;n--)
    {
        int temp=0;
        scanf("%s",B);
        int blen=strlen(B);
        for(int i=0;i<blen-alen+1;i++)
        {
            for (int j=0;j<alen;j++)
            {
                sub[j]=B[i+j];
            }
            for(int j=0;j<alen;j++)
            {
                if(A[j]!=sub[j])
                {
                    j=alen;
                }
                if(j==alen-1)
                {
                    temp=temp+1;
                }
            }
        }
        if(ans<=temp)   ans=temp;
    }
    printf("%d\n",ans);
}