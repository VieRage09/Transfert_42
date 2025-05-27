/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/24 00:56:06 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Mallocs and initialize an s_exec structure
// Assigns its arguments required to exec a cmd block
// Gets the correct fdin and fdout according to the cmd block we want to exec
// Mallocs a cmd tab containing only the cmd and its args 
// Returns the structure created
// Returns NULL on error
t_exec *init_s_exec(t_token *s_token, int *pipefd, int *rdpipe, char **env, int **hd_tab)
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
	s_exec->hd_tab = hd_tab;
	return (s_exec);
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
	t_exec *s_exec;
	int id;
	int *pipefd;
	int *rdpipe;
	int	**hd_tab;


	if (!s_token || !*env_pt || !*s_env)
	{
		printf("s_token or env_list of env is NULL\n");
		return (1);
	}
	rdpipe = malloc(sizeof(int));
	if (!rdpipe)
		return (1);
	*rdpipe = -1;
	hd_tab = new_hd_tab(s_token);
	if (!hd_tab)
		return (1);
	while (s_token)
	{
		if (create_pipe(s_token, &pipefd) > 0)
			return (3);
		s_exec = init_s_exec(s_token, pipefd, rdpipe, *env_pt, hd_tab);
		if (!s_exec)
			return (4);
		if (is_builtin(s_exec->cmd_block) > 0)
			id = exec_builtin(s_exec, s_env, env_pt); // Les builtins semble etre execute dans un process enfant uniquement lors qu'ils appartiennent a une pipeline
		else
			id = exec_cmd(s_exec, *s_env);
		if (update_hd_tab(s_token, &hd_tab) != 0)
			return (4);
		// Normalement l'enfant ne sort pas de exec  mais ATTENTION
		// if (s_exec->fdin != STDIN_FILENO)
		// 	if (close(s_exec->fdin) != 0)
		// 		perror("Close failed for fdin");
		// if (s_exec->fdout != STDOUT_FILENO)
		// 	if (close(s_exec->fdout) != 0)
		// 		perror("Close failed for fdout");
		continue_exec(&s_token, pipefd, rdpipe);
		free(s_exec);
		if (id < 0)
			return (5);
	}
	return (0);
}
bool	running = true;

void	exit_(int code)
{
	if (code == 1)
		printf("exit\n");
	else if (code == 2)
		printf("exit\n");
	running = false;
}

void	handle_sigint(int sig) // ( Ctrl + C)
{
	(void)sig;
	//rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

bool	empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

void	free_cuisine(t_token *tokens, char *str)
{
	free_tokens(tokens);
	free(str);	
}

int	main(int ac, char **av, char **env)
{
	char	*raw_fruits;
	t_token	*fruit_salad;
    t_env   *env_lst;
	int 	i;
	char	**env_cpy;
	int		ret;

    env_lst = create_env_lst(env);
	if (update_env_tab(env_lst, &env_cpy) != 0)
		return (1);
	signal(SIGINT, handle_sigint); // ( Ctrl-C )
	signal(SIGQUIT, SIG_IGN); // ( attention, Ctrl-\ est completement ignore)
	while(1)
	{
		raw_fruits = readline("\033[1;94mminishell> \033[0m");
		if (!raw_fruits) // Ctrl + D renvoi NULL, de cette facon il quitte le shell
			exit_(1);
		if (empty_line(raw_fruits))
			continue ;// passe a la prochain iteration du while (autorisee ?)
		add_history(raw_fruits);
		if (error_check(raw_fruits))
			continue ;
		fruit_salad = let_me_cook(raw_fruits, env_lst);
		tokens_cleaner(fruit_salad, env_lst);
		print_tokens(fruit_salad);
		ret = launch_exec(fruit_salad, &env_cpy, &env_lst);
		free_cuisine(fruit_salad, raw_fruits);
		while (wait(NULL) != -1)
		;
	}

	free_env_lst(env_lst);
	return (ret);
}
