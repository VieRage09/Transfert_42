/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:08:36 by tlebon            #+#    #+#             */
/*   Updated: 2023/12/04 19:11:47 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h> 
# include <unistd.h>
# include <stdlib.h>
# include"libft/libft.h"

int	ft_printf(const char *s, ...);

int	ft_print_char(char c);
int	ft_print_str(const char *s);
int	ft_print_pointer(void *p);
int	ft_print_int(int n);
int	ft_print_uns_int(unsigned int u);
int	ft_print_hex_low(int i);
int	ft_print_hex_up(int i);

#endif
