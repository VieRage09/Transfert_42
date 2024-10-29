/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/29 18:12:22 by lberne           ###   ########.fr       */
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

void	signals(void)
{
	signal(SIGINT, handle_sigint); // ( Ctrl-C )
	signal(SIGQUIT, SIG_IGN); // ( attention, Ctrl-\ est completement ignore)
}

void	init_minishell(t_data *data)
{
	data->tokens = NULL;
	data->env_lst = NULL;
	data->input = NULL;
	data->ret = 0;
	signals();
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	**env_cpy;

	init_minishell(&data);
    data.env_lst = create_env_lst(env);
	if (update_env_tab(data.env_lst, &env_cpy, 0) != 0)
		return (1);
	while(1)
	{
		data.input = readline("\033[1;94mminishell> \033[0m");
		if (!data.input) // Ctrl + D renvoi NULL, de cette facon il quitte le shell
			break ;
		if (empty_line(data.input))
			continue ;// passe a la prochain iteration du while (autorisee ?)
		add_history(data.input);
		if (error_check(data.input))
			continue ;
		if (!(data.tokens = let_me_cook(data.input, data.env_lst)))
			break ;
		print_tokens(data.tokens);
		data.env_lst->ret = launch_exec(data.tokens, &env_cpy, &data.env_lst);
		free_tokens(data.tokens);
		data.tokens = NULL;
	}

	free_all(&data);	
	ft_free_tab((void **)env_cpy);
	rl_clear_history();
	printf("exit\n");
	return (data.env_lst->ret);
}
