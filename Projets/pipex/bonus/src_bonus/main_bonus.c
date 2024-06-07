/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:20 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/05 18:25:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	print_pipe_tab(int **tab, int ac)
{
	for (int i = 0; i < ac - 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			ft_printf("%d(%d) : %d\n", i, j, tab[i][j]);
		}
	}
	return ;
}
char	**get_middle_cmd_tab(int ac, char **av)
{
	char	**tab;
	int		i;

	tab = malloc((ac - 4) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < ac - 5)
	{
		tab[i] = ft_strdup(av[i + 3]);
		if (!tab[i])
		{
			ft_free_tab((void **) tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	main(int ac, char **av, char **envp)
// int	main(int ac, char **av)
{
	int		**pipe_tab;
	int		pipe_count;
	pid_t	id1;
	pid_t	id2;

	pipe_tab = menu(ac);
	if (!pipe_tab)
		return (EXIT_FAILURE);
	// Pipes are well created but not yet redirected
	pipe_count = 0;
	id1 = launch_first_process(av[2], av[1], pipe_tab[0], envp);
	if (ac - 4 > 1)
		middle_cmd_loop(get_middle_cmd_tab(ac, av), pipe_tab, envp); // creer fonction pour chopper les cmd du milieu dans un tableau et qui le fini par NULL
	id2 = launch_last_process(av[ac - 2], av[ac - 1], pipe_tab[ac - 5], envp);
	// Fin du prog
	while (pipe_count < ac - 4)
		free_close_pipe(pipe_tab[pipe_count++]);
	return (get_status_code(id2)); // ????????????????????????????????
}
