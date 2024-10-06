/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/06 21:28:03 by tlebon           ###   ########.fr       */
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

///// BUILTIN /////////////////////////////////////////////////////////////////

// CD.C				1	X
int		change_directory(char *path);

// PWD.C			1	X
void	print_working_directory(void);

// ENV.C			1	X
int		print_env(char **env);
///////////////////////////////////////////////////////////////////////////////

// EXECUTE.C		3	X
int     execute_lone_cmd(char *cmd, char **env);

// BOOL.C           3   X
int     is_pipe(char *str);
int     is_input_redirector(char *str);
int     is_output_redirector(char *str);

// MANAGE_FD.C      4   X
int     open_infile(char *file_path);
int     open_outfile(char *file_path, int append);
int     get_fdin(char **cmd_tab, int position, char **prompt_tab);
int     get_fdout(char **cmd_tab, int position, char **prompt_tab);


int     prepare_cmd_tab(char ***cmd_tab);


#endif