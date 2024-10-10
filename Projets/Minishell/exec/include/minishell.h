/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/10 01:14:31 by tlebon           ###   ########.fr       */
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

#define R_IN			1         // "< redirect input"
#define R_OUT			2         // "> redirect output"
#define R_OUT_APPEND	3        // ">> redirect output in append mode"
#define HEREDOC			4        // "<< redirect input until specified delimiter"
#define ARG				5        // "argument of a command"
#define CMD				6        // "command"
#define PIPE			7        // "| use the left part as an arg for the right part"


typedef struct s_token // contient l'element de la commande + son type
{
    char			*str; // l'element 
    int				type; // le type
    struct s_token	*prev;
    struct s_token	*next;
}					t_token;

///// BUILTIN /////////////////////////////////////////////////////////////////

// CD.C				1	X
int		change_directory(char *path);

// PWD.C			1	X
void	print_working_directory(void);

// ENV.C			1	X
int		print_env(char **env);
///////////////////////////////////////////////////////////////////////////////

// EXECUTE.C		3	X
char	*get_cmd_path(char *cmd);
int     execute_lone_cmd(char *cmd, char **env);

// BOOL.C           3   X
int     is_pipe(char *str);
int     is_input_redirector(char *str);
int     is_output_redirector(char *str);

// MANAGE_FD.C      4   X
int     open_infile(char *file_path);
int     open_outfile(char *file_path, int append);


#endif