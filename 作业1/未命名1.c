#include <stdio.h>

int fact(int) __attribute__((cdecl));
int n,sum;

int main()
{
	printf("input n:");
	scanf("%d",&n);
	printf("%d!=%d\n",n,fact(n));
	system("pause");
	return 0;
}
