/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:34:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/27 19:42:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check si il y a des subtilitees :
// Avec le comportement de cd dans bash pour adapter le comportement 
// Avec getcwd notamment avec les parametres (leaks ? error management ?)
// Uses getcwd to get working directory then prints it
void print_working_directory(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);	
}