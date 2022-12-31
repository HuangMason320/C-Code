#include <stdio.h>

int main()
{
    float num;
    while(scanf("%f",&num)!=EOF)
    {
        int temp = *((int *)&num);
        for (int i = 31; i >= 0;i--)
        {
            if((temp&(1<<i))!=0)
                printf("1");
            else
                printf("0");
            if(i==0)
                printf("\n");
        }
    }
    return 0;
}