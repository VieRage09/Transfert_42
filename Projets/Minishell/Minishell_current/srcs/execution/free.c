/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:23:57 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/22 17:14:14 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_hd_tab_fd(int	**tab)
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

int	clean_close(int fd) // Tres bancal
{
	struct stat	info;
	if (fstat(fd, &info) == 0)
		if (close(fd) != 0)
			perror("Close failed");
	return (0);
}

void	free_s_manager(t_manager *s_manager)
{
	if (!s_manager)
		return ;
	if (s_manager->hd_tab)
	{
		if (close_hd_tab_fd(s_manager->hd_tab) != 0)
			ft_putstr_fd("Close error in close_hd_tab_fd function", 2);
		ft_free_tab((void **)s_manager->hd_tab);
	}
	if (s_manager->pipefd)
		free(s_manager->pipefd);
	if (s_manager->s_exec)
		free(s_manager->s_exec);
	free(s_manager);
}
