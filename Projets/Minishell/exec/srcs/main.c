/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/22 19:56:54 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Mallocs and initialize an s_exec structure
// Assigns its arguments required to exec a cmd block
// Gets the correct fdin and fdout according to the cmd block we want to exec
// Mallocs a cmd tab containing only the cmd and its args 
// Returns the structure created
// Returns NULL on error
t_exec *init_s_exec(t_token *s_token, int *pipefd, int *rdpipe, char **env, int ***hd_tab)
{
	t_exec *s_exec;

	if (!s_token || !env || !rdpipe || !hd_tab) // pipefd et rdpipe ??
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
	s_exec->hd_tab_pt = hd_tab;
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
		//Gerer les heredocs : parcourir dans l'ordre le prompt pour recup tous les heredocs ouverts
		// if (manage_heredoc() != 0)
		// 	return (2);
		if (create_pipe(s_token, &pipefd) > 0)
			return (3);
		s_exec = init_s_exec(s_token, pipefd, rdpipe, *env_pt, &hd_tab);
		if (!s_exec)
			return (4);
		if (is_builtin(s_exec->cmd_block) > 0)
			id = exec_builtin(s_exec, s_env, env_pt); // Les builtins semble etre execute dans un process enfant uniquement lors qu'ils appartiennent a une pipeline
		else
			id = exec_cmd(s_exec);
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


bool	empty_line(char *line)
{
	int	i;

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
	while(1)
	{
		i = 0;
		raw_fruits = readline("\033[1;94mminishell> \033[0m");
		//raw_fruits[ft_strlen(raw_fruits) + 1] = 0;
		if (empty_line(raw_fruits))
			continue ;// passe a la prochain iteration du while (autorisee ?)
		add_history(raw_fruits);
		if (error_check(raw_fruits))
			continue ;
		fruit_salad = let_me_cook(raw_fruits, env_lst);
		tokens_cleaner(fruit_salad, env_lst);
		print_tokens(fruit_salad);
		ret = launch_exec(fruit_salad, &env_cpy, &env_lst);
		free_tokens(fruit_salad);	
		while (wait(NULL) != -1)
		;
	}

	free_env_lst(env_lst);
	return (ret);
}
// int main(int ac, char **av, char **env)
// // int main(void)
// {
// 	t_token *s_token;
// 	t_token *cmd1;
// 	t_token *cmd2;
// 	t_token *cmd3;
// 	t_token *arg1;
// 	t_token *arg2;
// 	t_token *arg3;
// 	t_token *infile;
// 	t_token *outfile;
// 	t_token *r_in;
// 	t_token *r_out;
// 	t_token *pipe;
// 	t_token *pipe2;
// 	t_env	*s_env;
// 	if (ac == 0)
// 		return 1;
// 	printf("%s\n", av[0]);

// 	s_env = create_env_lst(env);
// 	cmd1 = malloc(sizeof(t_token));
// 	cmd2 = malloc(sizeof(t_token));
// 	cmd3 = malloc(sizeof(t_token));
// 	arg1 = malloc(sizeof(t_token));
// 	arg2 = malloc(sizeof(t_token));
// 	arg3 = malloc(sizeof(t_token));
// 	infile = malloc(sizeof(t_token));
// 	outfile = malloc(sizeof(t_token));
// 	r_in = malloc(sizeof(t_token));
// 	r_out = malloc(sizeof(t_token));
// 	pipe = malloc(sizeof(t_token));
// 	pipe2 = malloc(sizeof(t_token));

// 	s_token = cmd1;

// 	cmd1->str = "pwd";
// 	cmd1->type = CMD;
// 	cmd1->prev = NULL;
// 	cmd1->next = pipe;

// 	arg1->str = "-e";
// 	arg1->type = ARG;
// 	arg1->prev = cmd1;
// 	arg1->next = r_in;

// 	cmd2->str = "ls";
// 	cmd2->type = CMD;
// 	cmd2->prev = pipe;
// 	cmd2->next = arg2;

// 	arg2->str = "-a";
// 	arg2->type = ARG;
// 	arg2->prev = cmd2;
// 	arg2->next = pipe2;

// 	cmd3->str = "cat";
// 	cmd3->type = CMD;
// 	cmd3->prev = pipe;
// 	cmd3->next = arg3;

// 	arg3->str = "-e";
// 	arg3->type = ARG;
// 	arg3->prev = cmd3;
// 	arg3->next = r_out;

// 	r_in->str = "<";
// 	r_in->type = R_IN;
// 	r_in->prev = arg1;
// 	r_in->next = infile;

// 	infile->str = "test";
// 	infile->type = ARG;
// 	infile->prev = r_in;
// 	infile->next = pipe;

// 	r_out->str = ">";
// 	r_out->type = R_OUT;
// 	r_out->prev = arg2;
// 	r_out->next = outfile;

// 	outfile->str = "out";
// 	outfile->type = ARG;
// 	outfile->prev = r_out;
// 	outfile->next = NULL;

// 	pipe->str = "|";
// 	pipe->type = PIPE;
// 	pipe->prev = cmd1;
// 	pipe->next = cmd3;

// 	pipe2->str = "|";
// 	pipe2->type = PIPE;
// 	pipe2->prev = arg2;
// 	pipe2->next = cmd3;

// 	print_cmd(s_token);
// 	int	ret = launch_exec(s_token, env, s_env);
// 	while (wait(NULL) != -1)
// 		;
// 	return (ret);
// }


