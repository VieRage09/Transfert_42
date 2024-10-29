/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:23:57 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/28 18:36:28 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_hd_tab_fd(int	**tab)
{
	int	i;

	if (!tab || !*tab)
		return (1);
	i = 0;
	while (tab[i]) 
	{
		// Use fstat to check if each fd is still open
		if (close(tab[i][0]) != 0)
			perror("Close failed");
		i++;
	}
	return (0);
}

void	free_s_manager(t_manager *s_manager)
{
	if (!s_manager)
		return ;
	free(s_manager->rdpipe);
	if (s_manager->hd_tab)
	{
		if (close_hd_tab_fd(s_manager->hd_tab) != 0)
			ft_putstr_fd("Close error in close_hd_tab_fd function", 2);
		ft_free_tab((void **)s_manager->hd_tab);
	}
	// if (s_manager->s_exec)
	// 	free_s_exec(s_manager->s_exec);
	free(s_manager);
}

void	free_s_exec(t_exec *s_exec)
{
	if (!s_exec)
		return ;
	// if (s_exec->pipefd)
	// 	free(s_exec->pipefd);
	free(s_exec);
}