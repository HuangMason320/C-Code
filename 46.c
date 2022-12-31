#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int arr[1001][1001];
    int row[1001]={0};
    int col[1001]={0};
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&arr[j][i]);
            if(arr[j][i]>row[i])    row[i]=arr[j][i];
            if(i==0)    col[j]=arr[j][i];
            else if(arr[j][i]<col[j])   col[j]=arr[j][i];
        }
    }
    for(int i=0;i<n-1;i++)
    {
        printf("%d ",row[i]);
    }
    printf("%d\n",row[n-1]);
    for(int i=0;i<n-1;i++)
    {
        printf("%d ",col[i]);
    }
    printf("%d\n",col[n-1]);
}