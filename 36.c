#include <stdio.h>

int arr[11]={0};
void bin(int a)
{
    if(a>=512)  
    {
        arr[1]=1;
        a-=512;
    }
    if(a>=256)
    {
        arr[2]=1;
        a-=256;
    }
    if(a>=128)
    {
        arr[3]=1;
        a-=128;
    }
    if(a>=64)
    {
        arr[4]=1;
        a-=64;
    }
    if(a>=32)
    {
        arr[5]=1;
        a-=32;
    }
    if(a>=16)
    {
        arr[6]=1;
        a-=16;
    }
    if(a>=8)
    {
        arr[7]=1;
        a-=8;
    }
    if(a>=4)
    {
        arr[8]=1;
        a-=4;
    }
    if(a>=2)
    {
        arr[9]=1;
        a-=2;
    }
    if(a!=0)
    {
        arr[10]=1;
    }
    arr[11]='\0';
}
int main()
{
    int N;
    scanf("%d",&N);
    bin(N);
    int times=0;
    for(int i=10;i>=0;i--)
    {
        if(arr[i]==1)
        {
            times+=1;
            arr[i]=0;
        }
        else
        {
            arr[i]=1;
            break;
        }
    }
    int test=0;
    for(int i=0;i<11;i++)
    {
        if(arr[i]==1&&test==0)
        {
            test=1;
        }
        if(test==1)
        {
            printf("%d",arr[i]);
        }
    }
    printf(" %d",times);
}