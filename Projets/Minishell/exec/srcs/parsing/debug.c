/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:31:28 by lberne            #+#    #+#             */
/*   Updated: 2024/10/14 21:41:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bip_boup(int type)
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

void	read_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
}

void	tab_type_reader(char **tab) //for basic parsing ONLY (with bash_split)
{
	int	i;
	int	len;

	i = 0;
	while (tab[i])
	{
		//printf("%s\n", tab[i]);
		len = strlen(tab[i]);
		printf("\n\ntoken %d is type : ", i);
		if (!ft_strncmp(tab[i], "|", len))
			printf("%d (PIPE) ", PIPE);
		else if (!ft_strncmp(tab[i], "<", len))
			printf("%d (R_IN) ", R_IN);
		else if (!ft_strncmp(tab[i], "<<", len))
			printf("%d (HEREDOC) ", HEREDOC);
		else if (!ft_strncmp(tab[i], ">", len))
			printf("%d (R_OUT) ", R_OUT);
		else if (!ft_strncmp(tab[i], ">>", len))
			printf("%d (R_OUT_APPEND) ", R_OUT_APPEND);
		else if (i == 0 || !(strncmp(tab[i - 1], "|", strlen(tab[i - 1]))))
			printf("%d (CMD) ", CMD);
		else
			printf("%d (ARG) ", ARG);
		printf("< %s >\n", tab[i]);
		i++;
	}
	printf("\n");
}
