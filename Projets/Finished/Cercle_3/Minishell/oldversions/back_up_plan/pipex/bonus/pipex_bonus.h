/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:21:54 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/16 23:57:23 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h> // pour pipe, fork, access
# include <stdio.h>	// pour perror
# include <fcntl.h>	// pour pid_t et open 
# include <sys/wait.h>	// pour wait waitpid
# include "../lib/libft.h"

// EXEC_BONUS.C			5	V	N
int		execute(char *cmd, char **env);
void	launch_first_process(char *cmd, char **env, char *infile,
			int *read_pipe);
pid_t	launch_last_process(char *cmd, char **env, char *outfile,
			int *read_pipe);

// FILE_PIPE_BONUS.C	4	V	N
int		open_infile(char *file_path);
int		open_outfile(char *file_path, int append);
int		redirect(int *pipe_tab, int fd_read, int fd_write);
void	close_pipe(int	*pipe);

// HEREDOC_BONUS.C		5	v	N
int		hd_pipex(int ac, char **av, char **envp);

// PIPEX_BONUS.C		5	V	N	
char	**get_middle_cmd_tab(int ac, char **av);
void	middle_cmd_loop(char **cmd_tab, int *read_pipe, char **env);
int		get_status_code(int last_cmd_id, int cmd_num);
int		pipex(int ac, char **av, char **envp);

// UTILS_BONUS.C		4	V	N	
char	*get_cmd_path(char *cmd, char **env);

#endif
