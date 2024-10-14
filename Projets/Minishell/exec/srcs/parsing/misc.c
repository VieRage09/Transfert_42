/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:18:08 by lberne            #+#    #+#             */
/*   Updated: 2024/10/14 21:41:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
// int	quote_error(char *input)
// {
// 	int	i;
// 	int	s_quote;
// 	int	d_quote;
// 	char	q;

// 	i = 0;
// 	d_quote = 0;
// 	s_quote = 0;
// 	q = 'q';
// 	while (input[i])
// 	{
// 		if (d_quote >= 1 && s_quote >= 1 && input[i] != q)
// 			return (1);
// 		if (input[i] == 34)
// 		{
// 			if (d_quote >= 1)
// 				d_quote--;
// 			else if (d_quote == 0)
// 				d_quote++;
// 		}
// 		else if (input[i] == 39)
// 		{
// 			if (s_quote >= 1)
// 				s_quote--;
// 			else if (s_quote == 0)
// 				s_quote++;
// 		}
// 		q = input[i];
// 		i++;
// 	}
// 	if (d_quote > 0 || s_quote > 0)
// 		return (1);
// 	return (0);
// }

int	done(char *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst[i])
	{
		if (cmd_lst[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

void	exec_order(char *cmd_tree, char **input)
{
	int	i;
	char layer;
	
	layer = '5';
	i = 0;
	while (!done(cmd_tree))
	{
		if (cmd_tree[i] == layer)
		{
			printf("%s ", input[i + 1]);
			cmd_tree[i] = '0';
			i++;
			while (cmd_tree[i] == '4' || cmd_tree[i] == '3')
			{
				printf("%s ", input[i + 1]);
				cmd_tree[i] = '0';
				i++;
			}
			printf("\n");
		}
		if (!cmd_tree[i])
		{
			layer--;
			i = 0;
		}
		i++;
	}
}

char	type_reader(char *str)
{
	if (!str)
		return ('\0');
	if (!ft_strncmp(str, "|", 1))
	{
		return ('1');
	}
	if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1) 
			|| !ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
	{
		return ('2');
	}
	if (!ft_strncmp(str, "-n", 2))
	{
		return ('4');
	}
	if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) 
			|| !ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6)
			|| !ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3)
			|| !ft_strncmp(str, "exit", 4))
		return ('5');
	return ('3');
}

char	*tree_reader(int size, char **input)
{
	char	*res;
	int		i;
	int		y;

	res = (char *)malloc(sizeof(char) * size);
	if (!res)
		return (0);
	i = 0;
	y = 1;
	while (input[i])
	{
		res[i] = type_reader(input[y]);
		i++;
		y++;
	}
	res[y] = '\0';
	return (res);
}