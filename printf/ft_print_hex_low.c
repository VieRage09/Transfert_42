#include "ft_printf.h"

// Pour les nombre negatifs, printf natif affiche ffffffd6 pour -42, ft_printf affiche quant a lui -2a ???

static int	count_digit(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= (-1);
		count++;
	}
	while (n > 15)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static char	write_hex(long n)
{
	if (n > 15)
		return ('\0'); // Condition d arret a revoir
	else if (n > 9)
		return (n + 'a' - 10); 
	else
		return (n + '0');
}

int	ft_print_hex_low(int i)
{
	char	*s;
	int	size;
	int	cursor;
	long	nbr;
	

	nbr = (long) i;
	s = malloc((count_digit(nbr) + 1) * sizeof(char));
	if (!s)
		return (-1);
	cursor = count_digit(nbr) - 1;
	s[cursor + 1] = '\0';
	if (nbr < 0)
	{
		s[0] = '-';
		nbr *= (-1);
	}
	while(nbr > 15)
	{
		s[cursor] = write_hex(nbr % 16);
		nbr /= 16;
		cursor--;
	}
	s[cursor] = write_hex(nbr);
	size = ft_strlen(s);
	write(1, s, size);
	free(s);
	return (size);
}
