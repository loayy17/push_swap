/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:27:04 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:27:04 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_ptr(unsigned long n)
{
	int	len;

	len = 0;
	if (n != 0)
	{
		len += ft_printf_char('0');
		len += ft_printf_char('x');
		len += ft_printf_hex_putptr(n);
	}
	else
		len += write(1, "(nil)", 5);
	return (len);
}
