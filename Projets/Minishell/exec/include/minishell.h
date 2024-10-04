/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/01 18:52:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define	MINISHELL_H

#include "lib/libft.h"
#include <unistd.h>		// chdir, getcwd, fork
#include <stdio.h>		// printf
#include <stdlib.h>		// getenv
#include <fcntl.h>      // open

#include <sys/types.h> // opendir, readdir, closedir
#include <dirent.h>	   // //////////////////////////

// #include <readline/readline.h>	// readline
// #include <readline/history.h>	// add_history

#include <sys/wait.h>			// Wait duh


// CD.C				1	X
int		change_directory(char *path);

// PWD.C			1	X
void	print_working_directory(void);

// ENV.C			1	X
int		print_env(char **env);

// EXECUTE.C		3	X
int	execute_lone_cmd(char *cmd, char **env);

#endif