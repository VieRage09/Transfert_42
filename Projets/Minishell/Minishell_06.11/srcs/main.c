/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/06 16:48:09 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	heredoc = false;

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;
	char	**env_cpy;

	init_minishell(&data);
	if (!(data.env_lst = create_env_lst(env)))
	{
		free_all(&data);
		return (-1);
	}
	if (update_env_tab(data.env_lst, &env_cpy, 0) != 0)
		return (1);	data.ret = 1;
	while(1)
	{
		line = readline("\033[1;94mminishell>\033[0m ");
		if (!line)
			break ;
		if (empty_line(line))
			continue ;
		add_history(line);
		if (error_check(line))
			continue ;
		if (!(data.tokens = let_me_cook(line, &data)))
			break ;
		print_tokens(data.tokens);
		data.ret = launch_exec(data.tokens, &env_cpy, &data.env_lst);
		free_tokens(data.tokens);
		data.tokens = NULL;
		free(line);
	}
	free_all(&data);
	ft_free_tab((void **)env_cpy);
	rl_clear_history();
	printf("exit\n");
	return (data.ret);
}
