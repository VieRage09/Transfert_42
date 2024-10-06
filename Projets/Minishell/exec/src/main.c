/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/07 00:55:46 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int main(int ac, char **av, char **env)
{
	// t_list	*s_list;
	// int		i;

	// i = 1;
	// s_list = ft_lstnew(env[0]);
	// while (env[i])
	// {
	// 	ft_lstadd_back(&s_list, ft_lstnew(env[i]));
	// 	i++;
	// }
	// if (ac <= 1)
	// {
	// 	printf("Pas assez d'args\n");
	// 	return (1);
	// }
	// else
	// {
	// 	if (ac == 2)
	// 	{
	// 		if (ft_strncmp("pwd", av[1], 3) == 0)
	// 		{
	// 			print_working_directory();
	// 			return (0);
	// 		}
	// 		else if (ft_strncmp("env", av[1], 3) == 0)
	// 			return (print_env(env));
	// 		else
	// 			return(execute_lone_cmd(av[1], env));
	// 	}
	// 	if (ac == 3)
	// 	{
	// 		if (ft_strncmp("cd", av[1], 2) == 0)
	// 			return (change_directory(av[2]));
	// 	}
	// }
env[2] = NULL;
int i = ac;
printf("%i", i);
	// return (0);
	ft_print_str_tab(av);
	char *s = "cat -e > out";
	char **tab = ft_split(s, ' ');
	if (!tab)
		return (1);
	prepare_cmd_tab(&tab);
	ft_print_str_tab(tab);
	printf("Ayo\n");
	return (0);
}

int	prepare_cmd_tab(char ***cmd_tab)
{
	int		i;
	int		alloc_size;
	char	**updated_cmd_tab;

	i = 0;
	alloc_size = 0;
	while ((*cmd_tab)[i])
	{
		if (is_input_redirector((*cmd_tab)[i]) || is_output_redirector((*cmd_tab)[i]))
			i++;
		++alloc_size;
		i++;
	}
	updated_cmd_tab = malloc(alloc_size * sizeof(char *));
	if (!updated_cmd_tab)
		return (1);
	i = 0;
	alloc_size = 0;
	while ((*cmd_tab)[i])
	{
		if (is_input_redirector((*cmd_tab)[i]) || is_output_redirector((*cmd_tab)[i]))
			i++;
		else
			updated_cmd_tab[alloc_size++] = (*cmd_tab)[i];
		i++;
	}
	updated_cmd_tab[alloc_size] = (char *)0;
	*cmd_tab = updated_cmd_tab;
	return (0);
}

// int	execute_cmd(char **prompt_tab, int position, char **env)
// {
// 	char	**cmd_tab;
// 	int		fdin;
// 	int		fdout;

// 	cmd_tab = ft_split(prompt_tab[position], ' ');
// 	if (!cmd_tab)
// 		return (1);
// 	fdin = get_fdin(cmd_tab, prompt_tab, position);
// 	fdout = get_fdout(cmd_tab, prompt_tab, position);	
// 	if (fdin < 0 || fdout < 0)
// 		return (1);
// 	prepare_cmd_tab(&cmd_tab);
// 	return (execute(cmd_tab, fdin, fdout, env));
// }

// // Prompt_tab = {"infile < cmd", | . "cmd", |, "cmd > outfile" }
// int	execute_prompt(char **prompt_tab, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (prompt_tab[i])
// 	{
// 		if (execute_cmd(prompt_tab, i, env) != 0)
// 			return (1);
// 		i++;
// 	}	
// }
