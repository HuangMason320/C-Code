#include<stdio.h>
#include<string.h>

char s[1001], sub[1001];
int pre[1001], pfx[1001];

int main(void)
{
	int t;
	int l, r;
	int i, k, j;
	
	scanf("%s", s);
	scanf("%s", sub);
	scanf("%d", &t); 

	for(i = 0; i < strlen(s); i++){
		int count = 0;
		
		for(k = 0; k < strlen(sub); k++){
			if(s[i+k] == sub[k])
				count++ ;
		}
		if(count == strlen(sub))	pre[i+k-1] = 1;		
	}
	
	for(i = 1; i <= strlen(s); i++){
		pfx[i] = pfx[i-1]+pre[i];
	}
	
	for(i = 0; i < t; i++){
		scanf("%d %d", &l, &r);
		printf("%d\n", pfx[r-1] - pfx[l-1]);
	}
	return 0;
}
