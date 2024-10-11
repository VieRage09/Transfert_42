/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/11 20:53:42by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_exec *init_s_exec(t_token *s_token, int *pipefd, int *rdpipe, char **env)
{
	t_exec *s_exec;

	if (!s_token || !env)
		return (NULL);
	s_exec = malloc(sizeof(t_exec *));
	if (!s_exec)
		return (NULL);
	s_exec->fdin = find_fdin(s_token, rdpipe);
	s_exec->fdout = find_fdout(s_token, pipefd);
	if (s_exec->fdin < 0 || s_exec->fdout < 0)
		return (NULL);
	printf("fdin =		%i / fdout =	 %i\n", s_exec->fdin, s_exec->fdout);
	s_exec->cmd_tab = prepare_cmd_tab(s_token);
	if (!s_exec->cmd_tab)
	{
		printf("prepare_cmd_tab function error\n");
		return (4);
	}
	s_exec->env_tab = env;
	return (s_exec);
}

int launch_exec(t_token *s_token, char **env)
{
	t_exec *s_exec;
	// int fdin;
	// int fdout;
	// char **cmd_tab;
	int id;
	int *pipefd;
	int *rdpipe; // Pour premiere exec : Pas besoin d'etre init
				 // Pour seconde exec  : Est init a l'entree READ du premier pipe cree
				 // Pour troisieme exec: Doit toujours pointer vers l'entree READ du 1er pour l'enfant
				 // puis doit pointer vers l'entree READ du deuxieme pipe cree

	if (!s_token || !env)
	{
		printf("s_token or env_list of env is NULL\n");
		return (1);
	}
	while (s_token)
	{
		print_cmd(s_token);
		if (create_pipe(s_token, &pipefd) > 0)
			return (3);
		s_exec = init_s_exec(s_token, pipefd, rdpipe, env);
		ft_print_str_tab(s_exec->cmd_tab);

		id = fork();
		if (id == -1)
		{
			perror("Fork failed");
			return (5);
		}
		if (id == 0)
			execute_cmd(s_exec);
		// Sauf erreur le child reste et meurt dans execute_cmd
		s_token = search_next_pipe(s_token);
		if (s_token)
			s_token = s_token->next;
		// if (pipefd)
		// {
		// 	if (close(pipefd[0]) != 0 || close(pipefd[1]) != 0)
		// 		perror("Close failed");
		// }
	}
	return (0);
}

int main(int ac, char **av, char **env)
// int main(void)
{
	t_token *s_token;
	t_token *cmd1;
	t_token *cmd2;
	t_token *arg1;
	t_token *arg2;
	t_token *infile;
	t_token *outfile;
	t_token *r_in;
	t_token *r_out;
	t_token *pipe;
	if (ac == 0)
		return 1;
	printf("%s\n", av[0]);

	cmd1 = malloc(sizeof(t_token));
	cmd2 = malloc(sizeof(t_token));
	arg1 = malloc(sizeof(t_token));
	arg2 = malloc(sizeof(t_token));
	infile = malloc(sizeof(t_token));
	outfile = malloc(sizeof(t_token));
	r_in = malloc(sizeof(t_token));
	r_out = malloc(sizeof(t_token));
	pipe = malloc(sizeof(t_token));

	s_token = cmd1;

	cmd1->str = "cat";
	cmd1->type = CMD;
	cmd1->prev = NULL;
	cmd1->next = arg1;

	arg1->str = "-e";
	arg1->type = ARG;
	arg1->prev = cmd1;
	arg1->next = r_in;

	cmd2->str = "cat";
	cmd2->type = CMD;
	cmd2->prev = pipe;
	cmd2->next = arg2;

	arg2->str = "-e";
	arg2->type = ARG;
	arg2->prev = cmd2;
	arg2->next = r_out;

	r_in->str = "<";
	r_in->type = R_IN;
	r_in->prev = arg1;
	r_in->next = infile;

	infile->str = "test";
	infile->type = ARG;
	infile->prev = r_in;
	infile->next = pipe;

	r_out->str = ">";
	r_out->type = R_OUT;
	r_out->prev = arg2;
	r_out->next = outfile;

	outfile->str = "out";
	outfile->type = ARG;
	outfile->prev = r_out;
	outfile->next = NULL;

	pipe->str = "|";
	pipe->type = PIPE;
	pipe->prev = infile;
	pipe->next = cmd2;

	// t_token *command;
	// int fdin;
	// int fdout;
	// char	**cmd_tab;

	// fdin = find_fdin(command);
	// printf("fdin = %i : %s\n", fdin, get_next_line(fdin));

	// fdout = find_fdout(command);
	// printf("fdout = %i : %s\n", fdout, get_next_line(fdout));

	// cmd_tab = prepare_cmd_tab(command);
	// if (!cmd_tab)
	// 	printf("NUUUUUUL\n");

	// ft_print_str_tab(cmd_tab);
	// printf("cmd = %s\narg = %s\n", cmd_tab[0], cmd_tab[1]);
	print_cmd(s_token);
	launch_exec(s_token, env);
	while (wait(NULL) != -1)
		;
	return (0);
}