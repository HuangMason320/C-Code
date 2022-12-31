#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char arr[101][1001];
int n;

int cmp(const void *a, const void *b)
{
    char ab[2001]={'\0'}, ba[2001]={'\0'};
    strcpy(ab, a);
    strcat(ab, b);
    strcpy(ba, b);
    strcat(ba, a);
    int t = strcmp(ab, ba);
    return -t;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%s", arr[i]);
        }
        qsort(arr, n, 1001 * sizeof(char), cmp);
        for (int i = 0; i < n; i++)
            printf("%s", arr[i]);
        printf("\n");
    }
}