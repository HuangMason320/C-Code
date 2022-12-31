#include<stdio.h>
#include<stdlib.h>

typedef struct{
    char s[23];
    int A,B;
    int D;
}car;
car c[503];

int n,x,y,ans,best,tmp;

int cmp_diff(const void *x,const void *y)
{
  return ((car*)y)->D-((car*)x)->D;
}
  
int cmp_a(const void *x,const void *y)
{
  return ((car*)y)->A-((car*)x)->A;
}
  
int cmp_b(const void *x,const void *y)
{
  return ((car*)x)->B-((car*)y)->B;
}
  
int cmp_lex(const void *x,const void *y)
{
  return (strcmp(((car*)x)->s,((car*)y)->s));
}

int value(int k)
{
  int total=0,i;
  qsort(c,k,sizeof(car),cmp_a);
  qsort(c+k,n-k,sizeof(car),cmp_b);
  for(i=0;i<x;i++)
    total=total+c[i].A;
  for(i=n-y;i<n;i++)
    total=total+c[i].B;
  return total;
}

int main()
{
  int i;
  scanf("%d %d %d\n",&n,&x,&y);
  for(i=0;i<n;i++)
  {
    scanf("%s %d %d\n",c[i].s,&c[i].A,&c[i].B);
    c[i].D=c[i].A-c[i].B;
  }
    
  
  for(i=0;i<n;i++)
  {
    qsort(c,n,sizeof(car),cmp_diff);
    tmp=value(i);
    if(best<tmp)
    {
      best=tmp;
      ans=i;
    }
  }
  qsort(c,n,sizeof(car),cmp_diff);
  qsort(c,ans,sizeof(car),cmp_a);
  qsort(c+ans,n-ans,sizeof(car),cmp_b);
  qsort(c,x,sizeof(car),cmp_lex);
  for(i=0;i<x;i++)
    printf("%s\n",c[i].s);
  return 0;
}