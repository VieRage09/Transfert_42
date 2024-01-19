/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:55:48 by tlebon            #+#    #+#             */
/*   Updated: 2024/01/18 21:03:42 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H 
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*lucas_safe(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s); 
int	del_read_line(char *buff, int index);

#endif 

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif