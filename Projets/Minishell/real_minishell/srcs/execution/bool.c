/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:05:37 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/24 22:47:38 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_token *cmd_block)
{
	t_token	*cmd_token;

	cmd_token = search_next_cmd(cmd_block);
	if (!cmd_block)
		return (-1);
	if (ft_strncmp(cmd_block->str, "echo", ft_strlen(cmd_block->str)) == 0)
		return (1);
	if (ft_strncmp(cmd_block->str, "cd", ft_strlen(cmd_block->str)) == 0)
		return (1);
	if (ft_strncmp(cmd_block->str, "pwd", ft_strlen(cmd_block->str)) == 0)
		return (1);
	if (ft_strncmp(cmd_block->str, "export", ft_strlen(cmd_block->str)) == 0)
		return (1);
	if (ft_strncmp(cmd_block->str, "unset", ft_strlen(cmd_block->str)) == 0)
		return (1);
	if (ft_strncmp(cmd_block->str, "env", ft_strlen(cmd_block->str)) == 0)
		return (1);
	if (ft_strncmp(cmd_block->str, "exit", ft_strlen(cmd_block->str)) == 0)
		return (1);
	else
		return (0);

}

// Returns true is s_token type is equal to type
// Returns false otherwise
int	is_type(t_token *s_token, int type)
{
	if (s_token->type == type)
		return (1);
	else
		return (0);
}
