#include<stdio.h>
int main()
{
    double a,b;
    int c,d;
    scanf("%lf %lf %d",&a,&b,&c);
    if(c==0)
    {
        printf("%.0f",a*b);
    }
    else
    {
        printf("%.*f",c,a*b);
    }
    return 0;
}
