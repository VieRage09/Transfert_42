/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:05:37 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/13 20:41:15 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **cmd_tab)
{
	if (!cmd_tab)
		return (-1);
	if (ft_strncmp(cmd_tab[0], "echo", ft_strlen(cmd_tab[0])) == 0)
		return (1);
	if (ft_strncmp(cmd_tab[0], "cd", ft_strlen(cmd_tab[0])) == 0)
		return (1);
	if (ft_strncmp(cmd_tab[0], "pwd", ft_strlen(cmd_tab[0])) == 0)
		return (1);
	if (ft_strncmp(cmd_tab[0], "export", ft_strlen(cmd_tab[0])) == 0)
		return (1);
	if (ft_strncmp(cmd_tab[0], "unset", ft_strlen(cmd_tab[0])) == 0)
		return (1);
	if (ft_strncmp(cmd_tab[0], "env", ft_strlen(cmd_tab[0])) == 0)
		return (1);
	if (ft_strncmp(cmd_tab[0], "exit", ft_strlen(cmd_tab[0])) == 0)
		return (1);
	else
		return (0);

}