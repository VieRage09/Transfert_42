/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:33 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/17 19:31:11 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_name(char *name)
{
	int	i;

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

static int	already_exists(t_env *s_env, char *name)
{
	t_env	*curs;
	int		longest;

	curs = s_env;
	while (curs)
	{
		if (ft_strlen(curs->name) > ft_strlen(name))
			longest =  ft_strlen(curs->name);
		else
			longest = ft_strlen(name);
		if (strncmp(curs->name, name, longest) == 0)
			return (1);
		curs = curs->next;
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
int	exec_export(char **cmd_tab, t_env **s_env, char ***env)
{
	int		i;
	int		ret;
	t_env	*var;
	char	*value;
	char	*trimed_value;
	char	*name;

	if (!cmd_tab || !*s_env)
		return (1);
	i = 1;
	ret = 0;
	while (cmd_tab[i])
	{
		value = ft_strchr(cmd_tab[i], '=');
		if (!value)
			name = cmd_tab[i];
		else
			name = ft_substr(cmd_tab[i], 0, ft_strlen(cmd_tab[i]) - ft_strlen(value));
		if (!name)
			return (2);
		if (invalid_name(name))
		{
			ret = 1;
			i++;
			continue ;
		}
		if (!value)
		{
			i++;
			continue;
		}
		if (ft_strlen(value) == 1)
			trimed_value = "";
		else
			trimed_value = ft_substr(value, 1, ft_strlen(value));
		if (!trimed_value)
			return (3);
		if (already_exists(*s_env, name) == 0)
			append_env_lst(s_env, create_env(name, trimed_value)); // Attention a la gestion d'erreur ici
		else
		{
			var = find_variable(name, *s_env);
			free(var->str);
			var->str = malloc(sizeof(char));
			if (!var->str)
				return (4);
			var->str = ft_strdup(trimed_value);
		}
		update_env_tab(*s_env, env);
		i++;
	}
	return (ret);
}
