/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:20 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 21:11:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		pipe_tab[2];
	pid_t	id1;
	pid_t	id2;

	menu(ac, pipe_tab);
	id1 = launch_first_process(av[2], av[1], pipe_tab, envp);
	id2 = launch_last_process(av[3], av[4], pipe_tab, envp);
	// Fin du prog
	free_close_pipe(pipe_tab);
	return (get_status_code(id2)); // ????????????????????????????????
}
