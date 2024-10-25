/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:33 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/25 02:36:10 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int invalid_name(char *name)
{
	int i;

	if (!name)
		return (1);
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		printf("minishell : export : '%s': not a valid identifier\n", name);
		return (1);
	}
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			printf("minishell : export : '%s': not a valid identifier\n", name);
			return (1);
		}
		i++;
	}
	return (0);
}

// Iterates through s_env and checks whether an env named name exists
// Returns 1 if it exits
// Returns 0 otherwise
static int already_exists(t_env *s_env, char *name)
{
	t_env *curs;
	int longest;

	curs = s_env;
	while (curs)
	{
		if (ft_strlen(curs->name) > ft_strlen(name))
			longest = ft_strlen(curs->name);
		else
			longest = ft_strlen(name);
		if (ft_strncmp(curs->name, name, longest) == 0)
			return (1);
		curs = curs->next;
	}
	return (0);
}

static int assign_check_arg(char *var, char **value, char **name, int *ret)
{
	*value = ft_strchr(var, '=');
	if (!*value)
		*name = var;
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

// Appends a new node to env_lst if there is no "name" named node inside it
// If there is a "name" named node, change its value (str) to value
// Push the modifications of env_lst to env_tab with update_env_tab function
int update_env(t_env **env_lst, char *name, char *value, char ***env_pt)
{
	t_env *var;

	if (already_exists(*env_lst, name) == 0)
		append_env_lst(env_lst, create_env(name, value)); // Attention a la gestion d'erreur ici
	else
	{
		var = find_variable(name, *env_lst);
		free(var->str);
		var->str = ft_strdup(value);
	}
	if (update_env_tab(*env_lst, env_pt, 1) != 0)
		return (1);
	return (0);
}

// static void delete_env_node(t_env **s_env, t_env *node)
// {
// 	if (!*s_env || !node)
// 		return;
// 	free(node->name);
// 	free(node->str);
// 	if (node->prev && node->next)
// 	{
// 		node->prev->next = node->next;
// 		node->next->prev = node->prev;
// 	}
// 	else if (node->prev && !node->next)
// 		node->prev->next = NULL;
// 	else if (node->next && !node->prev)
// 	{
// 		node->next->prev = NULL;
// 		*s_env = node->next;
// 	}
// 	free(node->prev);
// 	free(node->next);
// 	return;
// }

// Prints all the env variables in alphabetical order with export in front
// of all the variables and the values of varibales quoted
int lone_export(t_env *s_env) // Ne semble pas afficher tout env (ex: var _ absente)
{
	t_env	*curs;
	t_env	*printed;
	char	*prevprint;

	if (!s_env)
		return (-1);
	curs = s_env;
	printed = curs;
	prevprint = "";
	while (curs)
	{
		while (curs)
		{
			if (ft_strncmp(curs->name, prevprint, ft_strlen(curs->name) + ft_strlen(prevprint)) > 0
				&& ft_strncmp(curs->name, printed->name, ft_strlen(curs->name) + ft_strlen(printed->name)) < 0)
				printed = curs;
			curs = curs->next;
		}
		if (ft_strncmp(prevprint, printed->name, ft_strlen(prevprint) + ft_strlen(printed->name)) == 0)
			break;
		printf("export %s=\"%s\"\n", printed->name, printed->str);
		prevprint = printed->name;
		curs = s_env;
	}
	return (0);
}

// cmd = export NAME=value
// Comportement :
// 0. Si export NAME (sans '=') --> rien ne se passe
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
int exec_export(char **cmd_tab, t_env **s_env, char ***env)
{
	int i;
	int ret;
	char *value;
	char *trimed_value;
	char *name;

	if (!cmd_tab || !*s_env || !*env)
		return (1);
	if (!cmd_tab[1])
		return (lone_export(*s_env));
	i = 1;
	ret = 0;
	while (cmd_tab[i])
	{
		if (assign_check_arg(cmd_tab[i++], &value, &name, &ret) != 0)
			continue;
		if (ft_strlen(value) == 1)
			trimed_value = "";
		else
			trimed_value = ft_substr(value, 1, ft_strlen(value));
		if (!trimed_value)
			return (3);
		if (update_env(s_env, name, trimed_value, env) != 0)
			return (4);
		// free(name);				// ATTENTION peut poser probleme si name et trimed_value ne sont pas malloc 
		// free(trimed_value);
	}
	return (ret);
}
