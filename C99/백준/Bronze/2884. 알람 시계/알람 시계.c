#include <stdio.h>

int main(void)
{
	int hour, min,result;
	
	scanf("%d %d", &hour, &min);

	result = (hour*60) + min-45;
	if (result < 0)
	{
		result = 24 * 60 + min - 45;
	}
	hour = result / 60;
	min = result % 60;
	printf("%d %d \n", hour, min);
	return 0;
}