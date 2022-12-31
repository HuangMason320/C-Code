#include <stdio.h>
#include <string.h>

int MOD=1e9+7;

int main()
{
    int t,x;
    scanf("%d",&t);

    for(t;t>0;t--)
    {
        char temp[(int)1e6];
        char s[(int)1e7];

        int left;   
        long long int add, l, s_len,t_len;
        
        scanf("%d",&x);
        scanf("%s",s);
        
        l=strlen(s);
        s_len=l;    

        for(int i=1;i<=x;i++)
        {
            left=s[i-1]-'0';
            add = ( (l-i) % MOD * ( left - 1 ) ) % MOD ;
            l = ( l + add ) % MOD ;

            if(s_len<=x && left>1)
            {
                int a=0;
                for (int z=i; z<s_len; z++) 
                {
                    temp[a]=s[z];
                    a++;
                }
                temp[s_len-i]='\0';
                t_len=s_len-i;
                for (int j=0; j<(left-1); j++) 
                {
                    if (s_len>x)
                    {
                        break;
                    }
                    strcat(s, temp);
                    s_len=s_len+t_len;
                }
            }
            if(l<0)     l+=MOD;
        }
        printf("%lld\n",l);
    }
    return 0;
}
