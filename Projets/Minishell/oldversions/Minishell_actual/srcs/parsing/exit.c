/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:07:56 by lberne            #+#    #+#             */
/*   Updated: 2024/11/25 16:18:07 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*atoi for long long int*/
long long int	ft_atolli(const char *nptr)
{
	int				i;
	long long int	nbr;
	int				sign;

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

/*norm...*/
unsigned long long	set_limit(char c)
{
	if (c == '-')
		return (-(long long)LLONG_MIN);
	else
		return (LLONG_MAX);
}

/*check if the error code is in range (long long int)*/
bool	is_long_long_int(const char *str)
{
	unsigned long long	limit;
	unsigned long long	result;
	int					digit;

	result = 0;
	if (!str || *str == '\0')
		return (false);
	if (*str == '-' || *str == '+')
	{
		limit = set_limit(*str);
		str++;
	}
	else
		limit = LLONG_MAX;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (false);
		digit = *str - '0';
		if (result > (limit - digit) / 10)
			return (false);
		result = result * 10 + digit;
		str++;
	}
	return (true);
}

void	non_num_err(char *code, t_data *data)
{
	printf("exit: %s: ", code);
	printf("numeric argument required\n");
	data->ret = 2;
}

/*handle the exit keyword with the correct return code, see man*/
bool	ft_exit(t_token *tokens, t_data *data)
{
	t_token	*current;

	if (tokens && tokens->str && match(tokens->str, "exit"))
	{
		current = tokens->next;
		if (current && current->str)
		{
			if (!is_long_long_int(current->str))
				return (non_num_err(current->str, data), 1);
			data->ret = ft_atolli(current->str) % 256;
		}
		if (current && current->next)
		{
			data->ret = 1;
			return (printf("exit: too many arguments\n"), false);
		}
		return (true);
	}
	return (false);
}
