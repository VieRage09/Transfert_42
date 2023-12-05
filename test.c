#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int	main()
{
	void	*p;
	p = malloc (12);
	void	*q;
	unsigned long s = (unsigned long) p;
	unsigned long t = (unsigned long) q;
	printf("%lu\n", s);
	printf("%p\n", p);
	printf("%lu\n", t);
	printf("%p\n", q);
	return 0;
}
