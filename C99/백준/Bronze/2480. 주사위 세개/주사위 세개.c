#include <stdio.h>

int main(void)
{
	int dice1, dice2, dice3,max;

	scanf("%d %d %d", &dice1, &dice2, &dice3);

	if (dice1 == dice2 && dice2 == dice3)
		printf("%d \n", 10000 + dice1 * 1000);
	else if (dice1 == dice2 || dice1 == dice3 || dice2 == dice3)
	{
		if (dice1 == dice2 || dice1 == dice3)
			printf("%d \n", 1000 + dice1 * 100);
		else
			printf("%d \n", 1000 + dice2 * 100);
	}
	else
	{
		max = dice1;
		if (max < dice2)
			max = dice2;
		if(max<dice3)
			max = dice3;
		printf("%d \n", max * 100);
	}
	return 0;
}