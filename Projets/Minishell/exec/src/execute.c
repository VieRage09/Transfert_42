/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:15:30 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/01 18:57:23 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *lst_str_chr(t_list *s_list, char *str)
{
	t_list *cursor;

	if (!s_list)
		return (NULL);
	cursor = s_list;
	while (cursor)
	{
		if (ft_strncmp((char *)cursor->content, str, ft_strlen(str)) == 0)
			return ((char *)cursor->content);
		cursor = cursor->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **cmd_tab)
{
	int	i;
	char	*absolute_path;
	char	*prepared_cmd;

	if (!cmd || !cmd_tab)
		return (NULL);
	prepared_cmd = ft_strjoin("/", cmd);	
	i = 0;
	while (cmd_tab[i])
	{
		absolute_path = ft_strjoin(cmd_tab[i], prepared_cmd);
		if (access(absolute_path, F_OK) == 0 && access(absolute_path, X_OK) == 0)
		{
			free(prepared_cmd);
			return (absolute_path);
		}
		i++;
	}
	return (NULL);
}

char *get_cmd_path(char *cmd)
{
	char	*path;
	char	**path_tab;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	if (!path_tab)
		return (NULL);
	return (get_path(cmd, path_tab));
}

int execute_lone_cmd(char *cmd, char **env)
{
	char	**cmd_tab;
	char	*path;
	int		id;

	if (!cmd || ft_str_is_wspace(cmd))
		cmd_tab = NULL;
	else
		cmd_tab = ft_split(cmd, ' ');
	if (cmd_tab)
		path = get_cmd_path(cmd_tab[0]);
	else
		path = NULL;
	if (path == NULL)
		path = cmd;
	printf("%s\n", path);
	id = fork();
	if (id == 0)
	{
		if (execve(path, cmd_tab, env) != 0)
			perror("Execve failed");
		return (127);
	}
	else
		wait(NULL);
	return (127);
}


// A partir d'une commande (string entre le debut et un pipe, 
// un pipe et la fin ou 2 pipes), renvoie le fd a utiliser comme input
int	get_fdin(char **cmd_tab, int position, char **prompt_tab)
{
	int		i;
	char	*infile_path;

	i = 0;
	while (cmd_tab[i])
	{
		if (is_input_redirector(cmd_tab[i]) && cmd_tab[i + 1])
			return (open_infile(cmd_tab[i + 1]));
		// TODO : Mettre en place le heredoc
		i++;
	}
	if (position > 0 && is_pipe(prompt_tab[position - 1]))
		return (?) // entree read du pipe d'avant
	return (0);
}

int	get_fdout(char **cmd_tab, int position, char **prompt_tab)
{
	int		i;
	char	*outfile_path;

	i = 0;
	while (cmd_tab[i])
	{
		if (is_output_redirector(cmd_tab[i]) && cmd_tab[i + 1])
			return (open_outfile(cmd_tab[i + 1], 0));
		i++;
	}
	if (prompt_tab[position + 1] && is_pipe(prompt_tab[position + 1]))
		return (?) // entree write du pipe d'apres
	return (1);
}

int execute_prompt(char **prompt_tab, char **env)
{
	char	**cmd_tab;
	int		i;
	int		fdin;
	int		fdout;
	int		pipefd[2];

	// OPen the pipe

	i = 0;
	while (prompt_tab[i])
	{
		cmd_tab = ft_split(prompt_tab[i], ' ');
		if (!cmd_tab)
			return (1);
		fdin = get_fdin(cmd_tab, i, prompt_tab);
		fdout = get_fdout(cmd_tab, i, prompt_tab);
		if (fdin == -1 || fdout == -1)
			return (2);
		fork();

	}
	return (0);
}

int	execute_cmd(char *cmd, int fdin, int fdout, char **env)
{

		redirect(dd)

}


// < Makefile cat | ls | echo > outfile