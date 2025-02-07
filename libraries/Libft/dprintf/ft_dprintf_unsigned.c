/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:34:27 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:34:28 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_unsigned(unsigned int n, int fd)
{
	int	len;

	len = 0;
	if (n <= UINT_MAX)
	{
		if (n >= 10)
		{
			len += ft_dprintf_unsigned(n / 10, fd);
			len += ft_dprintf_unsigned(n % 10, fd);
		}
		else
			len += ft_dprintf_char(n + '0', fd);
		return (len);
	}
	return (0);
}
