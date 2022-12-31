//Unlimited Triangle Work
#include<stdio.h>
#include<string.h>

long long int arr[(int)1e5+1];
long long int pfx[(int)1e5+1];

int main()
{
    int t, a, b, c, d;
    long long ans, k;

    scanf("%d", &t);
    while(t--){
        scanf("%d%d%d%d", &a, &b, &c, &d);
        for(int i = a; i <= b; i++){   //在 x+B 處+1, 在 x+C+1 處-1
            arr[i+b]++;
            arr[i+c+1]--;
        }
        for(int i = 1; i <= b+c; i++){  //累加a的統計結果,得x+y值為i會出現幾次
            arr[i] +=arr[i-1];
        }
        for(int i = 1; i <= b+c; i++){  //prefix累加a的統計結果
            pfx[i] = pfx[i-1] + arr[i];
        }

        ans = 0;
        for(int i = c; i <= d; i++){
            if(b+c > i)
                ans += pfx[b+c] - pfx[i];
        }

        printf("%lld\n", ans);
      
      	for(int i=0; i <= (int)1e5; i++){
            arr[i]=0;
            pfx[i]=0;
        }

    }
    return 0;
}