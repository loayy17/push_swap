/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_hex_uppercase.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:34:00 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:34:01 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_hex_uppercase(unsigned long n, int fd)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_dprintf_hex_uppercase(n / 16, fd);
		len += ft_dprintf_hex_uppercase(n % 16, fd);
	}
	else
		len += write(fd, &"0123456789ABCDEF"[n], 1);
	return (len);
}
