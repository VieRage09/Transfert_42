/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:33 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/17 02:09:00 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**names;
	t_env	*var;

	if (!cmd_tab || !*s_env)
		return (1);
	i = 1;
	ret = 0;
	while (cmd_tab[i])
	{
		names = ft_split(cmd_tab[i], '=');
		if (!names)
			return (2);
		if (invalid_name(names[0]))
		{
			printf("minishell : export : '%s': not a valid identifier\n", names[0]);
			ret = 1;
			ft_free_tab((void **)names);
			i++;
			continue ;
		}
		if (already_exists(*s_env, names[0]) == 0)
			append_env_lst(s_env, create_env(names[0], names[1])); // Attention a la gestion d'erreur ici
		else
		{
			var = find_variable(names[0], *s_env);
			free(var->str);
			var->str = malloc(sizeof(char));
			if (!var->str)
				return (3);
			var->str = ft_strdup(names[1]);
		}
		ft_free_tab((void **)names);
		update_env_tab(*s_env, env);
		i++;
	}
	return (ret);
}
