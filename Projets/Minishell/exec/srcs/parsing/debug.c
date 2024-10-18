/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:31:28 by lberne            #+#    #+#             */
/*   Updated: 2024/10/16 21:54:35 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bip_boup(int type) //sert a debug en affichant le type de chaque token
{
	if (type == 1)
		return ("\033[1;95mR_IN\033[0m");
	else if (type == 2)
		return ("\033[1;94mHEREDOC\033[0m");
	else if (type == 3)
		return ("\033[1;93mR_OUT\033[0m");
	else if (type == 4)
		return ("\033[1;96mR_OUT_APPEND\033[0m");
	else if (type == 5)
		return ("\033[1;91mPIPE\033[0m (et jambe de bois)");
	else if (type == 6)
		return ("\033[1;92mCMD\033[0m");
	else if (type == 7)
		return ("\033[1;97mARG\033[0m");
	else
		return ("wtf ?");
}

void	print_tokens(t_token *head)
{
	t_token	*current = head;
	while (current != NULL)
	{
		printf("Token : str = \033[46m%s\033[0m\n", current->str);
		printf("type : %d (%s)\n\n", current->type, bip_boup(current->type));
		current = current->next;
	}
}

void    display_env_lst(t_env *head)
{
    t_env   *current;

    current = head;
    while(current != NULL)
    {
        printf("NAME : %s\nSTR : %s\n", current->name, current->str);
        current = current->next; 
    }
}