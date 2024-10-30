/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:20 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/16 19:32:55 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int ac, char **av, char **envp)
// int	main(int ac, char **av)
{
	if (ac > 5 && ft_strncmp(av[1], "here_doc", 8) == 0)
		return (hd_pipex(ac, av, envp));
	if (ac > 4 && ft_strncmp(av[1], "here_doc", 8) != 0)
		return (pipex(ac, av, envp));
	else
	{
		ft_putstr_fd("This function takes 4 arguments or more\n", 2);
		return (EXIT_FAILURE);
	}
}
