/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:02:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/28 22:51:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Used to extract the return value of the child lastid, which should be
// the most right cmd block of the prompt
// If there is no children because the prompt consisted of only one non piped
// bin, lastid is the return value of that bin so lastid is returned
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
static t_exec	*init_s_exec(t_token *s_token, char **env)
{
	t_exec	*s_exec;

	if (!s_token || !env)
		return (NULL);
	s_exec = malloc(sizeof(t_exec));
	if (!s_exec)
		return (NULL);
	s_exec->cmd_block = s_token;
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
	s_manager->prev_pipe = NULL;
	s_manager->pipefd = NULL;
	if (search_next_token(s_token, HEREDOC) != NULL)
	{
		s_manager->hd_tab = new_hd_tab(s_token);
		if (!s_manager->hd_tab)
		{
			free(s_manager);
			return (NULL);
		}
	}
	else
		s_manager->hd_tab = NULL;
	return (s_manager);
}

// Execution loop
// Checks if pipes need to be created, then init s_exec structure
// Launch correct execution function, whether if the cmd block is bin or cmd
// and harvests its pid or its return value (if its a non piped bin)
// If needed, the hd_tab is updated and the loop goes on until the end of
// the prompt
// Returns id on success or -1 on failure
static int	execute_prompt(t_data *s_data, t_manager *s_manager)
{
	int	id;

	while (s_data->s_token)
	{
		if (create_pipe(s_manager, s_token) > 0)
			return (-1);
		s_manager->s_exec = init_s_exec(s_token, *env_pt);
		if (!s_manager->s_exec)
			return (-1);
		if (is_builtin(s_manager->s_exec->cmd_block) > 0)
			id = exec_builtin(s_manager, s_env, env_pt);
		else
			id = exec_cmd(s_manager, *s_env, env_pt);
		free(s_manager->s_exec);
		s_manager->s_exec = NULL;
		if (s_manager->hd_tab)
			if (update_hd_tab(s_token, &(s_manager->hd_tab)) != 0)
				return (-1);
		continue_exec(&s_token, s_manager);
		if (id < 0)
			return (-1);
	}
	return (id);
}

// Entry function for the execution
// Firstly makes some verifications to ensure that the parameters are non NULL
// Then init the struct s_manager that contains everything that execute_prompt
// function needs
// FREE ENCORE A REVOIR 
// Returns the correct status code or 1, 2 or 3 on error
// int	launch_exec(t_token *s_token, char ***env_pt, t_env **s_env)
int	launch_exec(t_data *s_data)
{
	t_manager	*s_manager;
	int			id;

	if (!s_data->tokens || !s_data->env_cpy || !s_data->env_lst)
	{
		printf("s_token or env_list of env is NULL\n");
		return (1);
	}
	s_manager = init_s_manager(s_data->tokens);
	if (!s_manager)
		return (130);
	// id = execute_prompt(s_token, env_pt, s_env, s_manager);
	id = execute_prompt(s_data, s_manager);
	free_s_manager(s_manager);
	if (id < 0)
		return (2);
	return (get_status_code(id));
}
