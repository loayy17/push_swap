/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:27:17 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:27:17 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n <= UINT_MAX)
	{
		if (n >= 10)
		{
			len += ft_printf_unsigned(n / 10);
			len += ft_printf_unsigned(n % 10);
		}
		else
			len += ft_printf_char(n + '0');
		return (len);
	}
	return (0);
}
