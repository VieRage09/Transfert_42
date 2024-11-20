/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:07:56 by lberne            #+#    #+#             */
/*   Updated: 2024/11/20 17:25:32 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*atoi for long long int*/
long long int	ft_atolli(const char *nptr)
{
	int	i;
	long long int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign = sign * (-1);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * nbr);
}

int is_long_long_int(const char *str) 
{
	int	sign;

	sign = 1;
	if (!str || *str == '\0')
        return 0;
    if (*str == '-')
	{
        sign = -1;
        str++;
    }
	else if (*str == '+')
        str++;
    if (!isdigit((unsigned char)*str))
        return 0;
    long long result = 0;
    long long limit = (sign == -1) ? -(long long)LLONG_MIN : LLONG_MAX;
    while (*str)
	{
        if (!isdigit((unsigned char)*str))
            return 0;
        int digit = *str - '0';
        if (result > (limit - digit) / 10)
            return 0;
        result = result * 10 + digit;
        str++;
    }
    return 1;
}

/*handle the exit keyword with the correct return code, see man*/
bool	ft_exit(t_token *tokens, t_data *data)
{
	t_token	*current;
	char	*str_ptr;

	if (tokens && tokens->str && match(tokens->str, "exit"))
	{
		current = tokens->next;
		if (current && current->next)
		{
			data->ret = 1;
			return (printf("exit: too many arguments\n"), false);
		}
		if (current && current->str)
		{
			str_ptr = current->str;
			while (*str_ptr)
			{
				if (!ft_isdigit(*str_ptr) || !is_long_long_int(current->str))
				{
					data->ret = 2;
					return (printf("exit: numeric argument required\n"), 1);
				}
				str_ptr++;
			}
			data->ret = ft_atolli(current->str) % 256;
		}
		return (true);
	}
	return (false);
}
