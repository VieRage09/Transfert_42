/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:06:40 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/22 17:53:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_pipe(t_token *s_token, int **pipefd)
{
	t_token *curs;

	if (!s_token)
		return (1);
	curs = s_token;
	while (curs)
	{
		if (is_type(curs, PIPE))
		{
			*pipefd = malloc(2 * sizeof(int));
			if (!*pipefd)
				return (2);
			if (pipe(*pipefd) != 0)
			{
				perror("Pipe failed");
				free(*pipefd);
				return (3);
			}
			printf("Pipe created\n");
			printf("Pipefd[0] = %i / Pipefd[1] = %i\n", (*pipefd)[0], (*pipefd)[1]);
			return (0);
		}
		curs = curs->next;
	}
	printf("No pipe created\n");
	*pipefd = NULL;
	return (-1);
}
