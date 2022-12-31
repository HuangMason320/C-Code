// Hexadecimal to Binary
// wrong
#include <stdio.h>
int main()
{
    int a = 0, t;
    char ansa[9];
    char s[2];
    scanf("%s", s);
    for (int i = 0; s[i]; i++)
    {
        if (s[i] <= '9')
        {
            t = s[i] - '0';
        }
        else
        {
            t = s[i] - 'A' + 10;
        }
        a = a * 16 + t;
    }
    while (a != 0)
    {
        if (a >= 128)
        {
            ansa[0] = 1;
            a -= 128;
        }
        if (a >= 64)
        {
            ansa[1] = 1;
            a -= 64;
        }
        if (a >= 32)
        {
            ansa[2] = 1;
            a -= 32;
        }
        if (a >= 16)
        {
            ansa[3] = 1;
            a -= 16;
        }
        if (a >= 8)
        {
            ansa[4] = 1;
            a -= 8;
        }
        if (a >= 4)
        {
            ansa[5] = 1;
            a -= 4;
        }
        if (a >= 2)
        {
            ansa[6] = 1;
            a -= 2;
        }
        if (a == 1)
        {
            ansa[7] = 1;
            a -= 1;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        printf("%d", ansa[i]);
    }
    return 0;
}
