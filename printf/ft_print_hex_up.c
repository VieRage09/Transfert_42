#include "ft_printf.h"

static int	count_digit(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= (-1);
		count++;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	write_hex(long n)
{
	if (n > 15)
		return ('\0'); // Condition d arret a revoir
	else if (n > 9)
		return (n + 'A' - 10); 
	else
		return (n + '0');
}

int	ft_print_hex_up(int i)
{
	char	*s;
	int	size;
	int	cursor;
	long	nbr;
	

	nbr = (long) i;
	s = malloc((count_digit(nbr) + 1) * sizeof(char));
	if (!s)
		return (-1);
	cursor = count_digit(nbr);
	s[cursor + 1] = '\0';
	if (nbr < 0)
		s[0] = '-';
	while(nbr > 15)
	{
		s[cursor] = write_hex(nbr % 16);
		nbr /= 16;
		cursor--;
	}
	size = ft_strlen(s);
	write(1, s, size);
	free(s);
	return (size);
}
