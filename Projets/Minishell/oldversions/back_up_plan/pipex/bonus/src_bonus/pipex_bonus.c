/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:36:10 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/16 23:46:26 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

// Duplicates from av all the cmd except the first and last
// Returns a tab with all of them on success
// Returns NULL on failure
char	**get_middle_cmd_tab(int ac, char **av)
{
	char	**tab;
	int		i;

	tab = malloc((ac - 4) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < ac - 5)
	{
		tab[i] = ft_strdup(av[i + 3]);
		if (!tab[i])
		{
			ft_free_tab((void **)tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

// Instructions for the child process
// Redirects the fd accordingly then execute the cmd vi execute function
static void	middle_child(char *cmd, char **env, int *pipefd, int *read_pipe)
{
	if (redirect(pipefd, *read_pipe, pipefd[1]) == -1)
	{
		free(read_pipe);
		exit(4);
	}
	if (close(*read_pipe) != 0)
		perror("Close failed");
	exit(execute(cmd, env));
}

// Supposed to handle all the stuff inbetween the first and last process
void	middle_cmd_loop(char **cmd_tab, int *read_pipe, char **env)
{
	int	i;
	int	id;
	int	pipefd[2];

	i = -1;
	while (cmd_tab[++i])
	{
		if (pipe(pipefd) != 0)
		{
			perror("Pipe failed");
			free(read_pipe);
			exit(EXIT_FAILURE);
		}
		id = fork();
		if (id == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		if (id == 0)
			middle_child(cmd_tab[i], env, pipefd, read_pipe);
		if (close(*read_pipe) != 0 || close(pipefd[1]) != 0)
			perror ("Close failed");
		*read_pipe = pipefd[0];
	}
}

// Waits for both childs to finish properly then returns the correct status_code
int	get_status_code(int last_cmd_id, int cmd_num)
{
	pid_t	wid;
	int		wstatus;
	int		last_cmd_wstatus;
	int		statuscode;

	last_cmd_wstatus = 0;
	while (cmd_num > 0)
	{
		wid = wait(&wstatus);
		if (wid < 0)
			perror("Wait failed");
		if (wid == last_cmd_id)
			last_cmd_wstatus = wstatus;
		--cmd_num;
	}
	statuscode = WEXITSTATUS(last_cmd_wstatus);
	return (statuscode);
}

// Manages the unfolding of the basic program
// Lauch all the process to execute cmd
// Returns the status code of the last process
int	pipex(int ac, char **av, char **envp)
{
	int		*read_pipe;
	pid_t	id2;
	char	**mid_cmd_tab;

	read_pipe = malloc(sizeof(int));
	if (!read_pipe)
		exit(EXIT_FAILURE);
	*read_pipe = 0;
	launch_first_process(av[2], envp, av[1], read_pipe);
	if (ac - 4 > 1)
	{
		mid_cmd_tab = get_middle_cmd_tab(ac, av);
		middle_cmd_loop(mid_cmd_tab, read_pipe, envp);
		ft_free_tab((void **)mid_cmd_tab);
	}
	id2 = launch_last_process(av[ac - 2], envp, av[ac - 1], read_pipe);
	free(read_pipe);
	return (get_status_code(id2, ac - 3));
}
