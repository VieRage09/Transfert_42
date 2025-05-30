/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/07 03:48:03 by tlebon           ###   ########.fr       */
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

#include <sys/wait.h>			// Wait duh

# include <limits.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
	int				ret;
	bool			printed;
    struct s_env    *next;   
    struct s_env    *prev; 
}               t_env;

typedef	struct s_data
{
	t_token	*tokens;
	t_env	*env_lst;
	char	**env_tab;
	int		ret;
}				t_data;

typedef struct s_exec
{
    t_token *cmd_block;
    int     *pipefd;
    char    **env_tab;
}               t_exec;

typedef struct s_manager
{
	t_exec	*s_exec;
	int		*rdpipe;
	int		**hd_tab;
}				t_manager;

///// BUILTIN /////////////////////////////////////////////////////////////////

// BIN_UTILS.C      4   V
t_env	*find_variable(char *name, t_env *s_env);
t_env	*copy_s_env(t_env *s_env);
int     already_exists(t_env *s_env, char *name);
char    *get_env_str(t_env *s_env, char *name);
int     set_env_str(t_env **s_env, char *name, char *str);

// CD.C				2	VC
int		exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt);

// ECHO.C			2	V
int		exec_echo(char **cmd_tab);

// ENV.C			1	V
int		exec_env(t_env *s_env);

// EXEC_BIN.C       4   VC
int		exec_builtin(t_manager *s_manager, t_env **s_env, char ***env_pt);

// EXPORT.C			5	VC
int		exec_export(char **args, t_env **s_env, char ***env_pt);

// PWD.C			1	V
int		exec_pwd(t_env *s_env);

// UNSET.C			2	X
int		exec_unset(char **cmd_tab, t_env **s_env, char ***env_pt);
void	free_env_node(t_env *node, t_env **s_env);

// UPDATE_ENV.C     5   V
int		update_env_tab(t_env *s_env, char ***env_pt, int do_free);
int     update_env(t_env **env_lst, char *name, char *value, char ***env_pt);

///////////////////////////////////////////////////////////////////////////////

// BOOL.C			2	V
int		is_builtin(t_token *cmd_block);
int     is_type(t_token *s_token, int type);

// COMMAND.C		4	V
char	**prepare_cmd_tab(t_token *s_token);
char	*get_cmd_path(t_env *s_env, char *cmd);

// EXEC_CMD.C		3	X
int		exec_cmd(t_manager *s_manager, t_env *s_env, char ***env_pt);
void	continue_exec(t_token **s_token, int *pipefd, int *rdpipe);

// FREE.C           2   X
void	free_s_manager(t_manager *s_manager);
void	free_s_exec(t_exec *s_exec);

// HERE_DOC.C       2   X
int     **new_hd_tab(t_token *s_token);
int     chose_hd_fd(int **hd_pipes_tab);
int		update_hd_tab(t_token *s_token, int ***hd_tab);

// IN_OUT_FILES.C	4   X
int     open_infile(char *file_path);
int     open_outfile(char *file_path, int append);
int     set_fd_in_out(int *fdin, int *fdout, t_manager *s_manager);
int		redirect_input(int fdin, int fdout);

// MANAGER.C		4	X
int		launch_exec(t_token *s_token, char ***env_pt, t_env **s_env);

// PIPE.C			1	X
int		create_pipe(t_token *s_token, int **pipefd);

// UTILS.C			2	V
void	print_cmd(t_token *s_token);
t_token	*search_next_cmd(t_token *s_token);
t_token	*search_next_token(t_token *s_token, int type);

////////////////////////////////////////////////////////////////////////////////

// PARSING.C
int		handle_special_token(char *ingr, int start, char *temp);
int		handle_normal_token(char *ingr, int start, char *temp);
int		chopper(t_token **res, char *ingr, int start);
t_token	*let_me_cook(char *ingredients, t_env *env_lst);

// TOKENS.C
int		token_len(char *token, t_env *env_lst);
t_token	*create_token(const char *str, int type);
void	append_token(t_token **head, t_token *new_token);

// ENV.C
char	*env_extractor(char *name, t_env *env_lst);
char	*get_env(char *token, int start, t_env *env_lst);
t_env   *create_env(char *name, char *str, bool printed);
void    append_env_lst(t_env **head, t_env *new_env);
t_env   *create_env_lst(char **v_env);

// TYPE_READERS.C
int		read_type(char	*chunk);
void	physio(t_token *fruit_salad);

// FINISHES.C
int		handle_normal(char *str, char *new_str, int start);
int		handle_dollars(char *str, char *new_str, int start, t_env *env_lst);
int		handle_quotes(char *str, char *new_str, int start, t_env *env_lst);
int		handle_clean(char *str, char *new_str, int start, t_env *env_lst);
void	finishes(t_token *tokens, t_env *env_lst);

// FREE.C
void	free_tokens(t_token *head);
void    free_env_lst(t_env  *head);
void	free_all(t_data	*data);

// ERRORS.c
bool	empty_line(char *line);
bool	quote_error(char *input);
bool	error_check(char *line);

// UTILS.C
bool	is_special(char c);
bool	is_quote(char c);
bool	is_wspace(char c);
bool	match(char *s1, char *s2);
void	ft_cat(char *dest, const char *src, const char c_src);

//	DEBUG.C
char	*bip_boup(int type);
void	print_tokens(t_token *head);
void    display_env_lst(t_env *head);

#endif