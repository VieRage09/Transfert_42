/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:06:40 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/11 00:44:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int create_pipe(t_token *s_token, int *pipefd[])
{
	t_token *curs;

	if (!s_token || !(*pipefd))
		return (1);
	curs = s_token;
	while (curs)
	{
		if (curs->type == PIPE)
		{
			if (pipe(*pipefd) != 0)
			{
				perror("Pipe failed");
				return (2);
			}
			printf("Pipe created\n");
			return (0);
		}
		curs = curs->next;
	}
	printf("No pipe created\n");
	*pipefd = NULL;
	return (-1);
}
