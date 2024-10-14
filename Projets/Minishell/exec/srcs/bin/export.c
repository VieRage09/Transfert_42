/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:33 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/14 18:59:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_s_env_node(char *name, char *str, t_env *prev)
{
	t_env	*s_env;

	s_env = malloc(sizeof(t_env));
	if (!s_env)
		return (NULL);
	s_env->name = name;
	s_env->str = str;
	s_env->prev = prev;
	s_env->next = NULL;
	return (s_env);
}

static int	invalid_name(char *name)
{
	int	i;

	if (!name)
		return (1);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
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
int	exec_export(char **cmd_tab, t_env *s_env, char ***env)
{
	t_env	*curs;
	int		i;
	int		ret;
	char	**name_value;

	if (!cmd_tab || !s_env)
		return (1);
	curs = s_env;
	i = 1;
	ret = 0;
	while (cmd_tab[i])
	{
		name_value = ft_split(cmd_tab[i], '=');
		if (!name_value)
			return (2);
		if (invalid_name(name_value[0]))
		{
			printf("minishell : export : '%s': not a valid identifier\n", name_value[0]);
			ret = 1;
			ft_free_tab((void **)name_value);
			continue ;
		}
		curs->next = new_s_env_node(name_value[0], name_value[1], curs);
		
		ft_free_tab((void **)name_value);
		curs = curs->next;
		i++;
	}
	update_env_tab(s_env, env);
	return (ret);
}
