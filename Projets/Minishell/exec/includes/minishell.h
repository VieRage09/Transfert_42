/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/23 18:58:38 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define	MINISHELL_H

#include "libft.h"
#include <unistd.h>		// chdir, getcwd, fork
#include <stdio.h>		// printf
#include <stdlib.h>		// getenv
#include <fcntl.h>      // open
#include <stdbool.h>	// booleans
#include <errno.h>      // duh

#include <sys/types.h> // opendir, readdir, closedir
#include <dirent.h>	   // //////////////////////////

// #include <readline/readline.h>	// readline
// #include <readline/history.h>	// add_history

#include <sys/wait.h>			// Wait duh

# define R_IN			1 		// "< redirect input"
# define HEREDOC		2		// "<< redirect input until specified delimiter"
# define R_OUT			3 		// "> redirect output"
# define R_OUT_APPEND	4		// ">> redirect output in append mode"
# define PIPE			5		// "| use the left part as an arg for the right part"
# define CMD			6		// "command"
# define ARG			7		// "argument of a command"

typedef struct s_token // contient l'element de la commande + son type
{
    char			*str; // l'element 
    int				type; // le type
	bool			hello_there;
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
    t_token *cmd_block;
    int     *pipefd;
    int     readpipe;
    char    **env_tab;
	int		**hd_tab;
}               t_exec;

///// BUILTIN /////////////////////////////////////////////////////////////////

// CD.C				1	X
int		exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt);

// ECHO.C			1	X
int		exec_echo();

// ENV.C			1	X
int		exec_env(char **env);

// EXPORT.C			1	X
int     update_env(t_env **env_lst, char *name, char *value, char ***env_pt);
int		exec_export(char **args, t_env **s_env, char ***env_pt);

// PWD.C			1	X
int		exec_pwd(t_env *s_env);

// UNSET.C			1	X
t_env	*find_variable(char *name, t_env *s_env);   // a peu pres equivalent avec get_env_str
int		exec_unset(char **cmd_tab, t_env **s_env, char ***env_pt);

// BIN_UTILS.C		1	X
int		update_env_tab(t_env *s_env, char ***env_pt);
char    *get_env_str(t_env *s_env, char *name);     // ----------------------
int     set_env_str(t_env **s_env, char *name, char *str);
///////////////////////////////////////////////////////////////////////////////

// BOOL.C			1	X
int		is_builtin(t_token *cmd_block);
int     is_type(t_token *s_token, int type);

// COMMAND.C		4	X
t_token	*search_next_cmd(t_token *s_token);
char	**prepare_cmd_tab(t_token *s_token);
char	*get_cmd_path(t_env *s_env, char *cmd);

// EXECUTE.C		1	X
int		exec_cmd(t_exec *s_exec, t_env *s_env);
int		exec_builtin(t_exec *s_exec, t_env **s_env, char ***env_pt);
void	continue_exec(t_token **s_token, int *pipefd, int *rdpipe);

// HERE_DOC.C       2   X
int     **new_hd_tab(t_token *s_token);
int     chose_hd_fd(int **hd_pipes_tab);
int		update_hd_tab(t_token *s_token, int ***hd_tab);

// IN_OUT_FILES.C	4   X
int     open_infile(char *file_path);
int     open_outfile(char *file_path, int append);
int     set_fd_in_out(int *fdin, int *fdout, t_exec *s_exec);
int		redirect_input(int fdin, int fdout);

// PIPE.C			1	X
int		create_pipe(t_token *s_token, int **pipefd);

// UTILS.C			2	X
char	*lst_str_chr(t_list *s_list, char *str);
void	print_cmd(t_token *s_token);
t_token	*search_next_pipe(t_token *s_token);



// PARSING
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"


// PARSING

bool	is_special(char c);
bool	is_quote(char c);
bool	is_wspace(char c);
int		chunk_len(char *ingredients, int step);
int		read_type(char	*chunk);
int		end_of_token(char *ingredients, int step);
t_token	*let_me_cook(char *ingredients, t_env *env_lst);
char	**bash_split(char const *s);
void	clear_str(char	*str);
size_t	subtil(char	*str);
void	physio(t_token *fruit_salad);

// VARIABLES D'ENVIRONNEMENT

t_env   *create_env(char *name, char *str);
void    append_env_lst(t_env **head, t_env *new_env);
t_env   *create_env_lst(char **v_env);
void    free_env_lst(t_env  *head);

// TOKENS

size_t	sizeof_token(char *ingr, int start, t_env *env_lst);
t_token	*create_token(const char *str, int type);
void	append_token(t_token **head, t_token *new_token);
void	free_tokens(t_token *head);
void	tokens_cleaner(t_token *tokens_head, t_env *env_head);

//ERRORS

bool	error_check(char *line);
bool	quote_error(char *input);

//SIGNALS

void	handle_sigint(int sig);

// DEBUG

void    display_env_lst(t_env   *lst);
void	print_tokens(t_token *head);
void	tab_type_reader(char **tab);
void	read_tab(char **tab);

#endif