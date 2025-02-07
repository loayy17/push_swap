/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_uppercase.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:26:32 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:26:32 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	ft_printf_hex_uppercase(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_printf_hex_uppercase(n / 16);
		len += ft_printf_hex_uppercase(n % 16);
	}
	else
		len += write(1, &"0123456789ABCDEF"[n], 1);
	return (len);
}
