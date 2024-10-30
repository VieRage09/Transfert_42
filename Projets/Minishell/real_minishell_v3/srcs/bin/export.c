/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:33 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/29 23:53:10 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if name starts with an alphabetic char or an _ and if it contains 
// only alphanumeric chars
// Returns 1 if the conditions are fullfilled, 0 otherwise
static int	invalid_name(char *name)
{
	int	i;

	if (!name)
		return (1);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		printf("minishell: export: '%s': not a valid identifier\n", name);
		return (1);
	}
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			printf("minishell: export: '%s': not a valid identifier\n", name);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if the string exported is valid and assigns name and value
// If var has an = char, assigns the chars after it to value and 
// the chars before to name
// If var doesn't have an = char, var is treated as a name only export
// Name is checked via invalid_name function: if invalid 1 is assigned to ret
// For the moment, if var doesn't have an = char, error is returned
// Returns 0 on succes, 1 on error
static int	assign_check_arg(char *var, char **value, char **name, int *ret)
{
	*value = ft_strchr(var, '=');
	if (!*value)
		*name = ft_strdup(var);
	else
		*name = ft_substr(var, 0, ft_strlen(var) - ft_strlen(*value));
	if (!name)
		return (1);
	if (invalid_name(*name))
	{
		*ret = 1;
		return (1);
	}
	if (!*value)
		return (1);
	return (0);
}

// Used when export is called w/o args
// Supposed to print all the exported variables in alphabetical order
static int	lone_export(char **env)
{
	t_env	*s_env_cpy;
	t_env	*curs;
	t_env	*printed;

	s_env_cpy = create_env_lst(env);
	if (!s_env_cpy)
		return (1);
	curs = s_env_cpy;
	printed = curs;
	while (curs)
	{
		while (curs)
		{
			if (curs->exported && ft_strncmp(curs->name, printed->name,
					ft_strlen(curs->name) + ft_strlen(printed->name)) < 0)
				printed = curs;
			curs = curs->next;
		}
		printf("export %s=\"%s\"\n", printed->name, printed->str);
		free_env_node(printed, &s_env_cpy);
		curs = s_env_cpy;
		printed = curs;
	}
	free_env_lst(s_env_cpy);
	return (0);
}

// cmd = export NAME=value
// Comportement :
// 0. Si export NAME (sans '=') --> export mais pas dans s_env (afficher que en lone_export)
// 1. Si NAME n'existe pas encore et est valide (quand est il valide ???)
// --> Cree une nvelle envariable
// 2. Si NAME existe deja dans env, remplace sa valeur par value (meme si value est vide 'NAME=')
// 3. Si NAME n'existe pas et value pas precisee
// --> Cree une nvelle envariable ne correspondant a rien

// Conditions de validite de NAME :
// 1. Doit commencer par une lettre ou par '_'
// 2. Seuls les lettres (maj et min) et les chiffres sont autorises ainsi que '_'
// Conditions de validite de value : a voir

// cmd = export arg1 arg2 arg3
// Suis le meme comportement que de base

// Valeur de retour :
// = 1 Des qu'il y a un unvalid name
// A PRECISER
int	exec_export(char **cmd_tab, t_env **s_env, char ***env)
{
	int		i;
	int		ret;
	char	*value;
	char	*trimed_value;
	char	*name;

	if (!cmd_tab || !*s_env || !*env)
		return (1);
	if (!cmd_tab[1])
		return (lone_export(*env));
	i = 1;
	ret = 0;
	while (cmd_tab[i])
	{
		if (assign_check_arg(cmd_tab[i++], &value, &name, &ret) != 0)
			continue ;
		trimed_value = ft_substr(value, 1, ft_strlen(value));
		if (!trimed_value)
			return (3);
		if (update_env(s_env, name, trimed_value, env) != 0)
			return (4);
		free(name);
		free(trimed_value);
	}
	return (ret);
}
