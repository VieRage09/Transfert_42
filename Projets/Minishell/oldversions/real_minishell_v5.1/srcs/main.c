/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/07 03:20:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig) // ( Ctrl + C)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, handle_sigint); // ( Ctrl-C )
	signal(SIGQUIT, SIG_IGN); // ( attention, Ctrl-\ est completement ignore)
}

void	init_minishell(t_data *data)
{
	data->tokens = NULL;
	data->env_lst = NULL;
	data->ret = 0;
	signals();
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;
	int		ret;

	init_minishell(&data);
	if (!(data.env_lst = create_env_lst(env))) // MAJ SHELL, SHLVL, et _=absolute path de minishell
	{
		free_all(&data);
		return (1);
	}
	if (update_env_tab(data.env_lst, &data.env_tab, 0) != 0)
		return (1);
	while(1)
	{
		line = readline("\033[1;94mminishell> \033[0m");
		if (!line)
			break ;
		if (empty_line(line))
			continue ;
		add_history(line);
		if (error_check(line))
			continue ;
		if (!(data.tokens = let_me_cook(line, data.env_lst)))
			break ;
		print_tokens(data.tokens);
		data.env_lst->ret = launch_exec(data.tokens, &data.env_tab, &data.env_lst);
		free_tokens(data.tokens);
		data.tokens = NULL;
		free(line);
	}
	ret = data.env_lst->ret;
	free_all(&data);
	ft_free_tab((void **)data.env_tab); // rajouter dans free_all
	rl_clear_history();
	printf("exit\n");
	return (ret);
}
