#include <stdio.h>

int main(void)
{
	int n1, n2;
	int result1,result2,result3,result4;

	scanf("%d %d", &n1, &n2);
	result1 = n1 * (n2 % 10);
	n2 = n2 / 10;
	result2 = n1 * (n2 % 10);
	result3 = n1 * (n2 / 10);
	result4 = result1 + result2 * 10 + result3 * 100;
	printf("%d \n", result1);
	printf("%d \n", result2);
	printf("%d \n", result3);
	printf("%d \n", result4);
	return 0;
}