#include<stdio.h>
#include<string.h>
#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))
#define LL long long int
#define INF 0x3f3f3f3f

int n, q, labor[5001][2], paint[5001];

int cal(int out)
{
    int wall[5001];
    for(int i=1;i<=n;i++)
        wall[i] = paint[i];
    for (int i = labor[out][0]; i <= labor[out][1]; i++)
        wall[i]--;

    int full=0;
    for(int i=1;i<=n;i++)
        if(wall[i]>0)full++;

    int prefix[5001] = {0};
    for(int i=1;i<=n;i++)
        prefix[i] = prefix[i - 1] + ((wall[i] == 1) ? 1 : 0);

    int minus = INF;
    for(int i =0;i<q;i++)
        if (i != out)
            minus = Min(minus, prefix[labor[i][1]] - prefix[labor[i][0] - 1]);

    return full-minus;

}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &q);
        for (int i = 0; i < q; i++)
        {
            scanf("%d%d", &labor[i][0], &labor[i][1]);
            for (int j = labor[i][0]; j <= labor[i][1]; j++)
                paint[j]++;
        }
        int ans = 0;
        for (int i = 0; i < q; i++)
            ans = Max(ans, cal(i));
        printf("%d\n", ans);
        memset(paint, 0, sizeof(paint));
    }
}