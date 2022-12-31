#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
char *arr[1001];
char knucles[1001][1001];

int compare(const void *a, const void *b)
{
    return strlen(*(char **)a) - strlen(*(char **)b);
}

int main()
{
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", knucles[i]);
        arr[i] = knucles[i];
    }
    qsort(arr, n, sizeof(char *), compare);
    for(int i=0;i<n-1;i++)
	{
        if (strstr(arr[i + 1], arr[i]) == NULL)
        {
            printf("NO\n");
            return 0;
		}
	}
    printf("YES\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", arr[i]);
    }

    return 0;
}