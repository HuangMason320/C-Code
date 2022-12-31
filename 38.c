#include <stdio.h>
#include <string.h>

int main()
{
    char arr[27];
    int n;
    scanf("%d",&n);
    if(n>26)
    {
        printf("I'm the god of Knuckles!\n");
    }
    else if(n==1)
    {
        printf("I'm the god of Knuckles!\n");
    }
    else
    {
        scanf("%s",arr);
        int len=strlen(arr);
        int ans=0;
        for(int i=0;i<len;i++)
        {
            for(int j=i+1;j<len;j++)
            {
                if(arr[i]==arr[j])
                {
                    ans=1;
                    break;
                }
            }
        }
        if(ans==1)  printf("I'm the god of Knuckles!\n");
        else    printf("Different makes perfect\n");
    }
    return 0;
}
