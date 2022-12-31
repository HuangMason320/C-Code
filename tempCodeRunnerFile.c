#include <stdio.h>

int main()
{
    float input;
    while(scanf("%f",&input)!=EOF)
    {
        int temp = *((int *)&input);
        for (int i = 31; i > 0; i--)
        {
            if((temp&(1<<i))!=0)
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
    return 0;
}