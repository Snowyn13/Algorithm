#include <stdio.h>

int main(void)
{
	int h, m,t;
	int h_r=0,m_r=0;
	
	scanf("%d %d", &h, &m);
	scanf("%d", &t);

	if (m + t >= 60)
	{
		h_r = (m + t) / 60;
		m_r = (m + t) % 60;
		h += h_r;
		m = m_r;
		if (h >= 24)
			h =h%24;
	}
	else
		m += t;
	
	printf("%d %d", h, m);
	return 0;
}