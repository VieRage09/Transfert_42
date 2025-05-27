/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/28 22:41:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_heredoc_stop = false;

void	ft_reset(t_data *data)
{
	free_tokens(data->tokens);
	data->tokens = NULL;
	free(data->line);
	data->line = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init_minishell(&data, ac);
	data.loop = true;
	if (!create_env_lst(env, &data))
		return (free_all(&data), -1);
	if (update_env_tab(data.env_lst, &data.env_cpy, 0) != 0)
		return (data.ret = 1, 1);
	while (data.loop)
	{
		data.line = readline("\033[1;94mminishell>\033[0m ");
		if (!data.line)
			break ;
		if (empty_line(data.line))
			continue ;
		add_history(data.line);
		if (error_check(data.line))
			continue ;
		if (!let_me_cook(&data))
			break ;
		print_tokens(data.tokens);
		data.ret = launch_exec(&data);
		ft_reset(&data);
	}
	free_all(&data);
	rl_clear_history();
	return (printf("exit\n"), data.ret);
}


// int	main(int ac, char **av, char **env)
// {
// 	t_data	data;
// 	int x = 1;
// 	char *line = ft_strdup(av[1]); 

// 	init_minishell(&data, ac);
// 	if (!create_env_lst(env, &data))
// 		return (free_all(&data), -1);
// 	if (update_env_tab(data.env_lst, &data.env_cpy, 0) != 0)
// 		return (data.ret = 1, 1);
// 	while (x)
// 	{
// 		data.line = line;
// 		//data.line = readline("\033[1;94mminishell>\033[0m ");
// 		if (!data.line)
// 			break ;
// 		if (empty_line(data.line))
// 			continue ;
// 		//add_history(data.line);
// 		if (error_check(data.line))
// 			continue ;
// 		if (!let_me_cook(&data))
// 			break ;
// 		print_tokens(data.tokens);
// 		data.ret = launch_exec(data.tokens, &data.env_cpy, &data.env_lst);
// 		ft_reset(&data);
// 		x = 0;
// 	}
// 	free_all(&data);
// 	//rl_clear_history();
// 	return (printf("exit\n"), data.ret);
// }

