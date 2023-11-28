
#include"libft/libft.h"
#include<stdarg.h>
#include<stdio.h>

//Ajouter une fonction qui retourne une string resultant de la concatenation de la variable string et de la portion entre un char % et la fin ou entre 2 char %

int ft_printf(const char *s, ...)
{
	va_list	ap;	
	size_t	curs_s;
	size_t	curs_r;
	char	*string;

	va_start(ap, s);
	curs_s = 0;
	curs_r = 0;
	string = malloc(sizeof(char) * (ft_strchr(s, '%') - s + 2));
	printf("Taille du malloc = %li\n", ft_strchr(s, '%') - s + 2);
	if (!string)
		return (-1);
	while (s[curs_s])
	{
		if (s[curs_s] == '%' && s[curs_s + 1] == 'c')
		{
			string[curs_r] = '\0';
			string = ft_strjoin(string, ft_itoa(va_arg(ap, int)));
			curs_s += 2;
			curs_r = ft_strlen(string);
		}
		else if (s[curs_s] == '%' && s[curs_s + 1] == 's')
		{
			string[curs_r] = '\0';
			string = ft_strjoin(string, va_arg(ap, char *));
			curs_s += 2;
			curs_r = ft_strlen(string);
		}
		else if (s[curs_s] == '%' && s[curs_s + 1] == 'i')
		{
			string[curs_r] = '\0';
			string = ft_strjoin(string, ft_itoa(va_arg(ap, int)));
			curs_s += 2;
			curs_r = ft_strlen(string);
		}
		else
		{
			if (curs_r == curs_s)
			{
				string[curs_r] = s[curs_s];
				curs_r++;
				curs_s++;
			}
			else
			{
				//Fonction a ajouter + genere une boucle infinie 
				string = ft_strjoin(string, ft_substr(s, curs_s, 15));
				curs_s = ft_strlen(string);
			}
		}
	}
	write(1, string, ft_strlen(string));
	curs_r = ft_strlen(string);
	free(string);
	va_end(ap);
	return (curs_r);
}

int	main()
{
	//ft_printf("Test Char : %c\n", 'c');

	ft_printf("Test String : %s\nYolo\n", "Je suis une string");
	
	//ft_printf("Test Int : %i\n", 1);
	return 0;
}
