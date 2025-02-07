/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:31:09 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:31:09 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include "libft.h"

int		ft_printf(const char *formater, ...);
int		ft_printf_char(char c);
int		ft_printf_string(char *args);
int		ft_printf_unsigned(unsigned int n);
size_t	ft_printf_hex(unsigned int n);
size_t	ft_printf_hex_uppercase(unsigned int n);
int		ft_printf_number(int n);
int		ft_printf_ptr(unsigned long n);
char	*ft_itoa(int n);
size_t	ft_printf_hex_putptr(unsigned long n);

#endif