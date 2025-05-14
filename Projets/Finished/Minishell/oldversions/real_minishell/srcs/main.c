/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/25 23:37:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_(int code)
{
	(void)code;
}

void	handle_sigint(int sig) // ( Ctrl + C)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

bool	empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

void	free_cuisine(t_token *tokens, char *str)
{
	free_tokens(tokens);
	free(str);	
}

void	init_tokens(t_token *token)
{
	token = NULL;
	token->str = NULL;
	token->type = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*raw_fruits;
	t_token	*fruit_salad;
    t_env   *env_lst;
	int 	i;
	char	**env_cpy;
	int		ret;

    env_lst = create_env_lst(env);
	if (update_env_tab(env_lst, &env_cpy, 0) != 0)
		return (1);
	signal(SIGINT, handle_sigint); // ( Ctrl-C )
	signal(SIGQUIT, SIG_IGN); // ( attention, Ctrl-\ est completement ignore)
	while(1)
	{
		raw_fruits = readline("\033[1;94mminishell> \033[0m");
		if (!raw_fruits) // Ctrl + D renvoi NULL, de cette facon il quitte le shell
			break ;
		if (empty_line(raw_fruits))
			continue ;// passe a la prochain iteration du while (autorisee ?)
		add_history(raw_fruits);
		if (error_check(raw_fruits))
			continue ;
		if (!(fruit_salad = let_me_cook(raw_fruits, env_lst)))
			break ;
		print_tokens(fruit_salad);
		env_lst->ret = launch_exec(fruit_salad, &env_cpy, &env_lst);
		free_cuisine(fruit_salad, raw_fruits);
	}
	free_env_lst(env_lst);
	ft_free_tab((void **)env_cpy);
	printf("exit\n");
	return (ret);
}
