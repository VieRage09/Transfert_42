#include<stdio.h>
#include"ft_printf.h"
#include"stdlib.h"

void	Test_return_value(int ft, int print)
{
	printf("Return : ");
	if (ft == print)
		printf("\033[92mOK\033[00m\n");
	else
	{
		printf("\033[91;01mKO\033[00m\n");
		printf("ft = %i\nprint = %i\n", ft, print);

	}
	return ;
}


// Soucis de priorisation ? ftprintf semble s effectuer avant printf wtf ? 

int	main(void)
{
	int	ft;
	int	print;
	
	printf("\033[34m///////////////////////////////////////////////////////////////////////////////////////////////////////////////\033[00m\n");
	printf("printf puis ft\n");
	//Test %c

	printf("Test c :\n");
	
	printf("1.\n");
	print = printf("%c\n", 'c');
	ft = ft_printf("%c\n", 'c');
	Test_return_value(ft, print);
	

	//Test %s
	
	printf("Test s :\n");
	
	printf("1.\n");
	print = printf("%s\n", "Yoda en slip");
	ft = ft_printf("%s\n", "Yoda en slip");
	Test_return_value(ft, print);

	//Test %p
	
	void	*p = NULL;
	void	*q = malloc(4);

	printf("Test p :\n");
	
	printf("1.\n");
	print = printf("%p\n", p);
	ft = ft_printf("%p\n", p);
	Test_return_value(ft, print);
	
	printf("2.\n");
	print = printf("%p\n", q);
	ft = ft_printf("%p\n", q);
	Test_return_value(ft, print);

	free(q);

	//Test %d
	
	printf("Test d :\n");
	
	printf("1.\n");
	print = printf("%d\n", 12);
	ft = ft_printf("%d\n", 12);
	Test_return_value(ft, print);

	//Test %i
	
	printf("Test i :\n");
	
	printf("1.\n");
	print = printf("%i\n", 14);
	ft = ft_printf("%i\n", 14);
	Test_return_value(ft, print);

	//Test %u
	
	printf("Test u :\n");
	
	printf("1.\n");
	print = printf("%u\n", 50);
	ft = ft_printf("%u\n", 50);
	Test_return_value(ft, print);

	//Test %x
	
	printf("Test x :\n");
	
	printf("1.\n");
	print = printf("%x\n", 42);
	ft = ft_printf("%x\n", 42);
	Test_return_value(ft, print);

	//Test %X
	
	printf("Test X :\n");
	
	printf("1.\n");
	print = printf("%X\n", 42);
	ft = ft_printf("%X\n", 42);
	Test_return_value(ft, print);

	//Test %%
	
	printf("Test %% :\n");
	
	printf("1.\n");
	print = printf("%%\n");
	ft = ft_printf("%%\n");
	Test_return_value(ft, print);







	return (0);
}
