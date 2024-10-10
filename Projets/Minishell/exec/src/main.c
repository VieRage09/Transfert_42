/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/10 02:15:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_cmd(t_token *s_token)
{
	t_token *curs;

	curs = s_token;
	while (curs)
	{
		ft_print_str(curs->str);
		ft_print_str(" ");
		curs = curs->next;
	}
	ft_print_str("\n");
}

// Iterates s_token from start (s_token) to a pipe token or end of list
// Returns a pointer to the first cmd token found
t_token *search_next_cmd(t_token *s_token)
{
	t_token *curs;

	curs = s_token;
	while (curs && curs->type != PIPE)
	{
		if (curs->type == CMD)
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}

// Iterates through s_token until it finds a pipe token or end of list
// If a R_IN is encountered, open the next arg and returns its fd
// If no R_IN is encountered, but there is a pipe before the searching area
// returns the fd of the WRITE end of pipefd
// Returns STDIN if nothing above happens
// TODO : handle heredoc
int find_fdin(t_token *s_token, int *pipefd)
{
	t_token *curs;

	curs = s_token;
	while (curs && curs->type != PIPE)
	{
		if (curs->type == R_IN && curs->next && curs->next->type == ARG)
			return (open_infile(curs->next->str));
		curs = curs->next;
	}
	if (s_token->prev && s_token->prev->type == PIPE)
	{
		// Envoyer le fd du pipefd[2], entree READ;
		return (pipefd[0]);
	}
	return (STDIN_FILENO);
}

// Iterates through s_token until it finds a pipe token or end of list
// If a R_OUT of R_OUT_APPEND is encountered
// opens the next arg in append mode or not and returns its fd
// If no R_OUT nor R_OUT_APPEND is encountered, but there is a pipe
// returns the fd of the WRITE end of pipefd
// Returns STDOUT if nothing above happens
int find_fdout(t_token *s_token, int *pipefd)
{
	t_token *curs;

	curs = s_token;
	while (curs->next && curs->type != PIPE)
	{
		if (curs->type == R_OUT && curs->next->type == ARG)
			return (open_outfile(curs->next->str, 0));
		if (curs->type == R_OUT_APPEND && curs->next->type == ARG)
			return (open_outfile(curs->next->str, 1));
		curs = curs->next;
	}
	if (curs->type == PIPE)
	{
		return (pipefd[1]);
		// Envoyer le fd du pipefd[2], entree WRITE;
	}
	return (STDOUT_FILENO);
}

// s_token MUST BE A CMD TOKEN
// Search for further ARG tokens after the CMD one then
// allocates tab accordingly
// Fills up tab with the cmd string and possible arg strings
// Ends the tab with (char *)0
char **prepare_cmd_tab(t_token *s_token)
{
	t_token *curs;
	char **tab;
	int n_arg;

	if (s_token->type != CMD)
		return (NULL);
	curs = s_token;
	n_arg = 0;
	while (curs->next && curs->next->type == ARG)
	{
		n_arg++;
		curs = curs->next;
	}
	tab = malloc((n_arg + 2) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = s_token->str;
	curs = s_token->next;
	n_arg = 1;
	while (curs && curs->type == ARG)
	{
		tab[n_arg] = curs->str;
		n_arg++;
		curs = curs->next;
	}
	tab[n_arg] = (char *)0;
	return (tab);
}

int redirect_input(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		perror("Dup2 failed");
		return (1);
	}
	// if (close (fdin) != 0)
	// 	perror("Close failed");
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		perror("Dup2 failed");
		return (2);
	}
	// if (close (fdout) != 0)
	// 	perror("Close failed");
	// Surement necessaire de fermer le pipe
	// Voire les fd dupliques genre : les commentaires
	return (0);
}

void execute_cmd(int fdin, char **cmd_tab, int fdout, char **env)
{
	char *path;
	int ret;

	ret = redirect_input(fdin, fdout);
	if (ret != 0)
	{
		printf("Redirect input error : %i\n", ret);
		return;
	}
	path = get_cmd_path(cmd_tab[0]);
	if (!path)
		path = cmd_tab[0];
	// if (close(fdin) != 0 || close(fdout) != 0)
	// 	perror("Close failed");
	if (execve(path, cmd_tab, env) != 0)
	{
		perror("Execve failed");
		return;
	}
}

int create_pipe(t_token *s_token, int *pipefd[])
{
	t_token *curs;

	if (!s_token || !(*pipefd))
		return (1);
	curs = s_token;
	while (curs)
	{
		if (curs->type == PIPE)
		{
			if (pipe(*pipefd) != 0)
			{
				perror("Pipe failed");
				return (2);
			}
			return (0);
		}
		curs = curs->next;
	}
	printf("No pipe created\n");
	*pipefd = NULL;
	return (-1);
}

int launch_exec(t_token *s_token, char **env)
{
	t_token *curs;
	t_token *cmd_token;
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
	curs = s_token;

	// 1. Chercher la commande et les fdin et fdout
	// 2. Preparer le cmd_tab
	// 3. Pipe, Fork et dup2 les fdin et fdout
	cmd_token = search_next_cmd(curs);
	if (!cmd_token)
	{
		printf("No command found\n");
		return (2);
	}
	printf("cmd token is : %s\n", cmd_token->str);
	if (create_pipe(s_token, &pipefd) > 0)
		return (3);
	fdin = find_fdin(curs, pipefd);
	fdout = find_fdout(curs, pipefd);
	printf("fdin = %i\nfdout = %i\n", fdin, fdout);
	cmd_tab = prepare_cmd_tab(cmd_token);
	if (!cmd_tab)
	{
		printf("prepare_cmd_tab function error\n");
		free(cmd_token);
		return (4);
	}
	ft_print_str_tab(cmd_tab);
	id = fork();
	if (id == -1)
	{
		perror("Fork failed");
		free(cmd_token);
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

	s_token = cmd;

	cmd->str = "cat";
	cmd->type = CMD;
	cmd->prev = NULL;
	cmd->next = arg;

	arg->str = "-e";
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
	infile->next = r_out;

	r_out->str = ">";
	r_out->type = R_OUT;
	r_out->prev = NULL;
	r_out->next = outfile;

	outfile->str = "testout";
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
	launch_exec(cmd, env);
	return (0);
}