// Easy Palindrome
#include <stdio.h>

int main()
{
    int N, C;
    scanf("%d.%d", &N, &C);
    int a, b;
    a = 100 * (N % 10) + 10 * ((N / 10) % 10) + N / 100;
    b = 100 * (C % 10) + 10 * ((C / 10) % 10) + C / 100;
    if (b >= 1000)
    {
        b = b % 1000;
        a += 1;
    }
    int ans1, ans2;
    ans2 = C + b;
    ans1 = N + a;
    if (ans2 >= 1000)
    {
        ans2 = ans2 % 1000;
        ans1 += 1;
    }
    printf("%d.%d\n", ans1, ans2);
}