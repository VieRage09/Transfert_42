/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:18:45 by lberne            #+#    #+#             */
/*   Updated: 2024/11/06 16:04:42 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*ctrl + C*/
void	handle_sigint(int sig)
{
	(void)sig;
	if (heredoc)
	{
		heredoc = false;
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

void	init_minishell(t_data *data)
{
	data->tokens = NULL;
	data->env_lst = NULL;
	data->ret = 0;
	signals();
}
