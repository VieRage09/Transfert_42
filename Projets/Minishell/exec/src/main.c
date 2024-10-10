/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/10 18:43:29 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int launch_exec(t_token *s_token, char **env)
{
	int fdin;
	int fdout;
	char **cmd_tab;
	int id;
	int *pipefd;

	if (!s_token || !env)
	{
		printf("s_token or env_list of env is NULL\n");
		return (1);
	}
	if (create_pipe(s_token, &pipefd) > 0)
		return (3);
	fdin = find_fdin(s_token, pipefd);
	fdout = find_fdout(s_token, pipefd);
	cmd_tab = prepare_cmd_tab(search_next_cmd(s_token));
	if (!cmd_tab)
	{
		printf("prepare_cmd_tab function error\n");
		return (4);
	}
	id = fork();
	if (id == -1)
	{
		perror("Fork failed");
		ft_free_tab((void **)cmd_tab);
		return (5);
	}
	if (id == 0)
		execute_cmd(fdin, cmd_tab, fdout, env);
	else
		wait(NULL);
	return (0);
}

int main(int ac, char **av, char **env)
// int main(void)
{
	t_token *s_token;
	t_token *cmd;
	t_token *arg;
	t_token *infile;
	t_token *outfile;
	t_token *r_in;
	t_token *r_out;
	// t_token *pipe;
	if (ac == 0)
		return 1;
	printf("%s\n", av[0]);

	cmd = malloc(sizeof(t_token));
	arg = malloc(sizeof(t_token));
	infile = malloc(sizeof(t_token));
	outfile = malloc(sizeof(t_token));
	r_in = malloc(sizeof(t_token));
	r_out = malloc(sizeof(t_token));
	// pipe = malloc(sizeof(t_token));
	// if (!cmd || !infile || !outfile || !r_in || !r_out || !pipe)
	// if (!cmd || !arg || !pipe)
	// return (1);

	s_token = r_in;

	cmd->str = "ls";
	cmd->type = CMD;
	cmd->prev = NULL;
	cmd->next = arg;

	arg->str = "-a";
	arg->type = ARG;
	arg->prev = NULL;
	arg->next = r_out;

	r_in->str = "<";
	r_in->type = R_IN;
	r_in->prev = NULL;
	r_in->next = infile;

	infile->str = "test";
	infile->type = ARG;
	infile->prev = NULL;
	infile->next = cmd;

	r_out->str = ">";
	r_out->type = R_OUT;
	r_out->prev = NULL;
	r_out->next = outfile;

	outfile->str = "out";
	outfile->type = ARG;
	outfile->prev = NULL;
	outfile->next = NULL;

	// pipe->str = "|";
	// pipe->type = PIPE;
	// pipe->prev = NULL;
	// pipe->next = NULL;

	// t_token *command;
	// int fdin;
	// int fdout;
	// char	**cmd_tab;
	// command = search_next_cmd(cmd);
	// printf("Command found : %s\n", command->str);

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
	return (0);
}