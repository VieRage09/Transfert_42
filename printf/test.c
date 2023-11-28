#include"libftprintf.h"
#include"libft/libft.h"
#include<stdio.h>

int	main()
{
	//String
	ft_printf("Test String : %s\n", "Salut");	
	printf("Test String : %s\n", "Salut");	
	
	//Int
	ft_printf("Test int : %i\n", 4);
	printf("Test int : %i\n", 4);
	
	//Char
	ft_printf("Test Char : %c\n", 'c');
	printf("Test Char : %c\n", 'c');
	
	//Pointer
	ft_printf("Test pointer : %p",   );
	printf("Test pointer : %p",   );
	
	//Decimal
	ft_printf("Test deci : %d",   );
	printf("Test deci : %d",   );

	//Uns Decimal
	ft_printf("Test Uns : %u",   );
	printf("Test Uns : %u",   );

	//hexa
	ft_printf("Test hexa : %x",   );
	printf("Test hexa : %x",   );

	//HEXA
	ft_printf("Test HEXA : %X",   );
	printf("Test HEXA : %X",   );

	return (0);
}
