#include <stdio.h>
int m,n;
int qr,qm,ql,cr,cm,cl;
int ans;
void dfs(int x,int y)
{
    if(x == m && y == n)
    {
        ans++;
        return;
    }
    if(x != m)
    {
        int tqr = qr, tcl = cl, tqm = qm, tql = ql, tcm = cm, tcr = cr;
        int tmp = qr | qm | ql | cr | cm | cl;
        for(int i=0;i<n+m;i++)
        {
            if (((1 << i) & tmp) == 0)
            {
                qr = qr | (1<<i);
                qm = qm | (1<<i);
                ql = ql | (1<<i);
                qr = qr<<1;
                ql = ql>>1;
                cr = cr>>1;
                cl = cl<<1;
                dfs(x+1,y);
                qr = tqr, cl = tcl, qm = tqm, ql = tql, cm = tcm, cr = tcr;
            }
        }
    } 
    if(y != n){
        int tqr = qr, tcl = cl, tqm = qm, tql = ql, tcm = cm, tcr = cr;
        int tmp = qr | qm | ql | cm;
        for (int i = 0; i < n + m; i++)
        {
            if (((1 << i) & tmp) == 0)
            {
                cr = cr | (1 << i);
                cm = cm | (1 << i);
                cl = cl | (1 << i);
                qr = qr << 1;
                ql = ql >> 1;
                cr = cr >> 1;
                cl = cl << 1;
                dfs(x, y + 1);
                qr = tqr, cl = tcl, qm = tqm, ql = tql, cm = tcm, cr = tcr;
            }
    }
  }
}
int main()
{
    scanf("%d%d", &m, &n);
    dfs(0, 0);
    printf("%d\n", ans);
}