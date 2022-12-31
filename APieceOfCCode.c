// A piece of C code
#include <stdio.h>
// move n disks from a to b using c as a buffer
void hanoi(int a, int b, int c, int n)
{
    if (n == 0)
        return;
    hanoi(a, c, b, n - 1); // move the top n-1 disks from a to c
    printf("Move the #%d disk from Tower %d to Tower %d\n", n, a, b);
    hanoi(c, b, a, n - 1); // move the top n-1 disks from c to b
}

int main(void)
{
    int n; // number of disks
    scanf("%d", &n);
    hanoi(1, 3, 2, n);
    return 0;
}