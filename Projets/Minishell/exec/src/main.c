/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/01 18:54:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int main(int ac, char **av, char **env)
{
	t_list	*s_list;
	int		i;

	i = 1;
	s_list = ft_lstnew(env[0]);
	while (env[i])
	{
		ft_lstadd_back(&s_list, ft_lstnew(env[i]));
		i++;
	}
	if (ac <= 1)
	{
		printf("Pas assez d'args\n");
		return (1);
	}
	else
	{
		if (ac == 2)
		{
			if (ft_strncmp("pwd", av[1], 3) == 0)
			{
				print_working_directory();
				return (0);
			}
			else if (ft_strncmp("env", av[1], 3) == 0)
				return (print_env(env));
			else
				return(execute_lone_cmd(av[1], env));
		}
		if (ac == 3)
		{
			if (ft_strncmp("cd", av[1], 2) == 0)
				return (change_directory(av[2]));
		}
	}

	return (0);
}