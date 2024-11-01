/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:02:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/01 20:45:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_status_code(pid_t lastid)
{
	pid_t	wid;
	int		wstatus;
	int		last_status;

	last_status = -1;
	wid = waitpid(-1, &wstatus, 0);
	while (wid != -1)
	{
		if (wid == lastid)
			last_status = wstatus;
		wid = waitpid(-1, &wstatus, 0);
	}
	if (last_status == -1)
		return (lastid);
	return (WEXITSTATUS(last_status));
}

// Mallocs and initialize an s_exec structure
// Assigns its arguments required to exec a cmd block
// Gets the correct fdin and fdout according to the cmd block we want to exec
// Mallocs a cmd tab containing only the cmd and its args 
// Returns the structure created
// Returns NULL on error
static t_exec *init_s_exec(t_token *s_token, int *pipefd, int *rdpipe, char **env)
{
	t_exec *s_exec;

	if (!s_token || !env || !rdpipe) // pipefd et rdpipe ??
		return (NULL);
	s_exec = malloc(sizeof(t_exec));
	if (!s_exec)
		return (NULL);
	s_exec->cmd_block = s_token;
	if (pipefd)
		s_exec->pipefd = pipefd;
	else
		s_exec->pipefd = NULL;
	s_exec->readpipe = *rdpipe;
	s_exec->env_tab = env;
	return (s_exec);
}

// Mallocs and initialize the struct s_manager with proper data
// Returns it properly initialized
// Returns NULL on failure
static t_manager	*init_s_manager(t_token *s_token)
{
	t_manager	*s_manager;

	if (!s_token)
		return (NULL);
	s_manager = malloc(sizeof(t_manager));
	if (!s_manager)
		return (NULL);
	s_manager->s_exec = NULL;
	s_manager->rdpipe = malloc(sizeof(int));
	if (!s_manager->rdpipe)
	{
		free(s_manager);
		return (NULL);
	}
	*(s_manager->rdpipe) = -1;
	if (search_next_token(s_token, HEREDOC) != NULL)
	{
		s_manager->hd_tab = new_hd_tab(s_token);
		if (!s_manager->hd_tab)
		{
			free(s_manager->rdpipe);
			free(s_manager);
			return (NULL);
		}
	}
	else
		s_manager->hd_tab = NULL;
	return (s_manager);
}

// Entry function used to prepare everyting and execute the prompt
// Creates a loop, which means thatEvery cycle :
// A pipe is created if needed
// An s_struct is initialized 
// An execution function is called, whether the cmd block is a builtin or a cmd
// The reading head (s_token) of the prompt is set to the next cmd block
// The loop stops when every cmd block have been executed

// TODO : 
//	- Recupere la return value
//	- Mettre en place le system de wait pour process zombie
//	- Gere le cas ou les fonctions d'exec fail et retourne une valeur au lieu d'exit
int launch_exec(t_token *s_token, char ***env_pt, t_env **s_env)
{
	t_manager	*s_manager;
	int id;
	int *pipefd;


	if (!s_token || !*env_pt || !*s_env)
	{
		printf("s_token or env_list of env is NULL\n");
		return (1);
	}
	s_manager = init_s_manager(s_token);
	if (!s_manager)
		return (2);
	while (s_token)
	{
		if (create_pipe(s_token, &pipefd) > 0)
			return (3);
		s_manager->s_exec = init_s_exec(s_token, pipefd, s_manager->rdpipe, *env_pt);
		if (!s_manager->s_exec)
			return (4);
		if (is_builtin(s_manager->s_exec->cmd_block) > 0)
			id = exec_builtin(s_manager, s_env, env_pt);
		else
			id = exec_cmd(s_manager, *s_env, env_pt);
		if (s_manager->hd_tab)
			if (update_hd_tab(s_token, &(s_manager->hd_tab)) != 0)
				return (5);
		continue_exec(&s_token, pipefd, s_manager->rdpipe);
		if (id < 0)
			return (6);
		free_s_exec(s_manager->s_exec);
		if (pipefd)
			free(pipefd);
	}
	free_s_manager(s_manager);
	return (get_status_code(id));
}
