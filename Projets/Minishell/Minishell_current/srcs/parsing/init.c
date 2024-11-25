/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:45 by lberne            #+#    #+#             */
/*   Updated: 2024/11/25 18:09:30 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*ctrl + C*/
void	handle_sigint(int sig)
{
	(void)sig;
	if (g_heredoc)
	{
		g_heredoc = false;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_minishell(t_data *data, int ac)
{
	if (ac > 1)
		printf("minishell : no arguments requiered\n");
	data->tokens = NULL;
	data->env_lst = NULL;
	data->line = NULL;
	data->ret = 0;
	signals();
}
