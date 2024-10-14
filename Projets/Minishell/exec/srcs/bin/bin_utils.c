/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:02:56 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/14 17:34:02 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_tab(t_env *s_env, char ***env_pt)
{
	if (!s_env || !(*env_pt))
		return (1);
	printf("Env tab updated (non faut faire la fonction)\n");
	
	return (0);
}