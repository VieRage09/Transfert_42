/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:55:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/25 02:00:19 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a pipe and write inside with get_next_line on STDIN
// When the dilimiter is encountered, input is freed, the writing end of the pipe
// is closed and a pointer to the pipe is returned
// Returns NULL on error
static int	*write_new_hd_pipe(char *delimiter)
{
	char	*input;
	int		*new_pipe;

	if (!delimiter)
		return (NULL);
	new_pipe = malloc(2 * sizeof(int));
	if (!new_pipe)
		return (NULL);
	if (pipe(new_pipe) != 0)
	{
		perror("Pipe failed");
		return (NULL);
	}
	ft_putstr(">");
	input = get_next_line(STDIN_FILENO);
	while (input)
	{
		if (ft_strlen(input) == ft_strlen(delimiter) + 1
			&& ft_strncmp(delimiter, input, ft_strlen(delimiter)) == 0)
		{
			free(input);
			if (close(new_pipe[1]) != 0)
				perror("Close failed");
			return (new_pipe);
		}
		write(new_pipe[1], input, ft_strlen(input));
		free(input);
		ft_putstr(">");
		input = get_next_line(STDIN_FILENO);
	}
	return (NULL);
}

// Iterates on the cmd prompt pointed to by s_token and counts the number of heredoc
// Mallocs a tab with the correct number of pipes needed and fills them 
// Returns NULL on error
int	**new_hd_tab(t_token *s_token)
{
	t_token	*curs;
	int		**hd_pipes_tab;
	int		size;
	
	if (!s_token)
		return (NULL);
	curs = s_token;
	size = 0;
	while (curs)
	{
		if (is_type(curs, HEREDOC) && curs->next && is_type(curs->next, ARG))
			size++;
		curs = curs->next;
	}
	// if (size < 1)
	// 	return (NULL);
	hd_pipes_tab = malloc((size + 1) * sizeof(int *));
	curs = s_token;
	size = 0;
	while (curs)
	{
		if (is_type(curs, HEREDOC) && curs->next && is_type(curs->next, ARG))
		{
			hd_pipes_tab[size] = write_new_hd_pipe(curs->next->str);
			if (!hd_pipes_tab[size])
				return (NULL); // Plus free les autres deja crees
			++size;
		}
		curs = curs->next;
	}
	return (hd_pipes_tab);
}

int	chose_hd_fd(int **hd_pipes_tab)
{
	int	i;

	if (!hd_pipes_tab)
		return (-1);
	i = 0;
	while(hd_pipes_tab[i])
	{
		if (hd_pipes_tab[i][1] == -2)
			i++;
		else
			return (hd_pipes_tab[i][0]);
	}
	return (-1);
}

int	update_hd_tab(t_token *s_token, int ***hd_tab)
{
	t_token	*curs;
	int		i;

	if (!s_token || !(*hd_tab))
		return (1);
	curs = s_token;
	while (curs)
	{
		if (is_type(curs, PIPE))
			return (0);
		if (is_type(curs, HEREDOC) && curs->next && is_type(curs->next, ARG))
		{
			i = 0;
			while ((*hd_tab)[i])
			{
				if ((*hd_tab)[i][1] == -2)
					i++;
				else
				{
					(*hd_tab)[i][1] = -2;
					return (0);
				}
			}
		}
		curs = curs->next;
	}
	return (0);
}
