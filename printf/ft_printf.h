/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:08:36 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/28 19:16:28 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef	LIBFTPRINTF_H
#define LIBFTPRINTF_H
#include "libft/libft.h"
#include <stdarg.h>
#include <stddef.h> 
#include <unistd.h>
#include <stdlib.h>

int	ft_printf(const char *s, ...);

int	ft_print_int(int n);
int	ft_print_str(char *s);
int	ft_print_char(char c);
int	ft_print_pointer(void *p);
int	ft_print_uns_int(unsigned int u);

#endif
