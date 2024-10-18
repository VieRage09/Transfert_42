/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:55:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/17 22:59:18 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_here_doc(char *delimiter)
{
	char	*input;
	int		temp_pipe[2];

	if (pipe(temp_pipe) != 0)
	{
		perror("Pipe failed");
		return (1);
	}
	input = get_next_line(0);
	while (input)
	{
		if (ft_strlen(input) == ft_strlen(delimiter) + 1
			&& ft_strncmp(delimiter, input, ft_strlen(delimiter)) == 0)
		{
			// if (redirect(pipefd, temp_pipe[0], pipefd[1]) == -1)
				// exit(4);
			// close_pipe(temp_pipe);
			free(input);
			// exit(execute(cmd, env));
		}
		write(temp_pipe[1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
	}
}