/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/13 08:44:57 by tlebon           ###   ########.fr       */
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
}				t_token;

typedef struct  s_env
{
	char			*name;
    char            *str;
    struct s_env    *next;   
    struct s_env    *prev; 
}               t_env;

typedef struct s_exec
{
    int     fdin;
    int     fdout;
    char    **cmd_tab;
    char    **env_tab;
}               t_exec;

///// BUILTIN /////////////////////////////////////////////////////////////////

// CD.C				1	X
int		exec_cd(char *path);

// ECHO.C			1	X
int		exec_echo();

// ENV.C			1	X
int		exec_env(char **env);

// EXIT.C			1	X
int		exec_exit();

// EXPORT.C			1	X
int		exec_export(char **args, t_env *s_env);

// PWD.C			1	X
int		exec_pwd(void);

// UNSET.C			1	X
int		exec_unset();

///////////////////////////////////////////////////////////////////////////////

// BOOL.C			1	X
int		is_builtin(char **cmd_tab);

// COMMAND.C		4	X
t_token	*search_next_cmd(t_token *s_token);
char	**prepare_cmd_tab(t_token *s_token);
char	*get_cmd_path(char *cmd);

// EXECUTE.C		1	X
int		exec_cmd(t_exec *s_exec);
int		exec_builtin(t_exec *s_exec);
void	continue_exec(t_token **s_token, int **pipefd, int *rdpipe);

// IN_OUT_FILES.C	5   X
int     open_infile(char *file_path);
int     open_outfile(char *file_path, int append);
int		find_fdin(t_token *s_token, int *rdpipe);
int		find_fdout(t_token *s_token, int *pipefd);
int		redirect_input(int fdin, int fdout);

// PIPE.C			1	X
int		create_pipe(t_token *s_token, int **pipefd);

// UTILS.C			2	X
char	*lst_str_chr(t_list *s_list, char *str);
void	print_cmd(t_token *s_token);
t_token	*search_next_pipe(t_token *s_token);
#endif