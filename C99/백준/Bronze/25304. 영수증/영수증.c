#include <stdio.h>

int main(void)
{
	int X, N, a, b;
	int suma=0;

	scanf("%d", &X);
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &a,&b);
		suma += (a * b);
	}

	if (suma == X)
		printf("Yes");
	else
		printf("No");
	
	return 0;
}