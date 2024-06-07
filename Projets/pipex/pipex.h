/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:21:54 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 23:02:32 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // pour EXIT_SUCCESS ??
# include <unistd.h> // pour pipe, fork, access
# include <stdio.h>	// pour perror
# include <fcntl.h>	// pour pid_t et open 
# include <sys/wait.h>	// pour wait waitpid
# include "lib/libft.h"

// FILE_PIPE.C	4
int		open_infile(char *file_path);
int		open_outfile(char *file_path);
int		redirect(int *pipe_tab, int fd_read, int fd_write);
void	free_close_pipe(int *pipe_tab);

// EXEC.C		4
int		execute(char *cmd, char **env);
pid_t	launch_first_process(char *cmd, char *infile, int *pipe_tab, char **env);
pid_t	launch_last_process(char *cmd, char *outfile, int *pipe_tab, char **env);
int		get_status_code(int last_cmd_id);

// UTILS.C		5	
void	menu(int ac, int *pipe_tab);
char	*get_cmd_path(char *cmd, char **env);


#endif
