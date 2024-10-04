
#include "../include/minishell.h"

int	is_pipe(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|')
		return (1);
	return (0);
}

int	is_input_redirector(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '<')
		return (1);
	return (0);
}

int	is_output_redirector(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '>')
		return (1);
	return (0);
}