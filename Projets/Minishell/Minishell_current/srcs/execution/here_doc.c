/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:55:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/27 20:01:33 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a pipe and write inside with get_next_line on STDIN
// When the delimiter is encountered, input is freed, the writing end of the pipe
// is closed and a pointer to the pipe is returned
// Returns NULL on error

void	sig_set(void)
{
    struct sigaction old_sigint;
    struct sigaction sa;
    sa.sa_handler = heredoc_sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, &old_sigint);
	g_heredoc_stop = 0;
}

static int	*write_new_hd_pipe(char *delimiter)
{
	char	*input;
	int		*new_pipe;

	sig_set();
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
		if (g_heredoc_stop)
			break ;
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
		input = get_next_line(STDIN_FILENO); // erreur la ?
	}
	free(input);
	if (close(new_pipe[1]) != 0)
		perror("Close failed");
	free(new_pipe);
	return (NULL);
}

// static int	*write_new_hd_pipe(char *delimiter)
// {
// 	char	*input;
// 	int		*new_pipe;


//     // Save old signal handlers
//     struct sigaction old_sigint;
//     struct sigaction sa;

//     // Set up new handler for SIGINT
//     sa.sa_handler = heredoc_sigint_handler;
//     sa.sa_flags = 0;
//     sigemptyset(&sa.sa_mask);
//     sigaction(SIGINT, &sa, &old_sigint);
// 	if (!delimiter)
// 		return (NULL);
// 	new_pipe = malloc(2 * sizeof(int));
// 	if (!new_pipe)
// 		return (NULL);
// 	if (pipe(new_pipe) != 0)
// 	{
// 		perror("Pipe failed");
// 		return (NULL);
// 	}
// 	ft_putstr(">");
// 	input = gnl(STDIN_FILENO);
// 	while (input && !g_heredoc_stop)
// 	{
// 		if (g_heredoc_stop)
// 		{
// 			g_heredoc_stop = 0;
// 			break ;
// 		}
// 		if ((ft_strlen(input) == ft_strlen(delimiter) + 1
// 			&& ft_strncmp(delimiter, input, ft_strlen(delimiter)) == 0))
// 		{
// 			free(input);
// 			if (close(new_pipe[1]) != 0)
// 				perror("Close failed");
// 			return (new_pipe);
// 		}
// 		write(new_pipe[1], input, ft_strlen(input));
// 		free(input);
// 		ft_putstr(">");
// 		input = gnl(STDIN_FILENO); // erreur la ?
// 		if (close(new_pipe[1]) != 0)
// 			perror("Close failed");
// 	}
// 	ft_putstr_fd("gnl finished\n", 2);
// 	free(input);
// 	if (close(new_pipe[1]) != 0)
// 		perror("Close failed");
// 	free(new_pipe);
// 	return (NULL);
// }

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
	hd_pipes_tab = malloc((size + 1) * sizeof(int *));
	if (!hd_pipes_tab)
		return (NULL);
	curs = s_token;
	size = 0;
	while (curs)
	{
		if (is_type(curs, HEREDOC) && curs->next && is_type(curs->next, ARG))
		{
			hd_pipes_tab[size] = write_new_hd_pipe(curs->next->str);
			if (!hd_pipes_tab[size])
			{
				ft_free_tab((void **)hd_pipes_tab);
				return (NULL);
			}
			++size;
		}
		curs = curs->next;
	}
	hd_pipes_tab[size] = NULL;
	return (hd_pipes_tab);
}

int	chose_hd_fd(int **hd_pipes_tab)
{
	int	i;
	int	fdin;

	if (!hd_pipes_tab)
		return (-1);
	i = 0;
	while(hd_pipes_tab[i])
	{
		if (hd_pipes_tab[i][1] == -2)
			i++;
		else
		{
			hd_pipes_tab[i][1] = -2;
			return (hd_pipes_tab[i][0]);
		}
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
	while (curs && !is_type(curs, PIPE))
	{
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
					break ;
				}
			}
		}
		curs = curs->next;
	}
	return (0);
}
