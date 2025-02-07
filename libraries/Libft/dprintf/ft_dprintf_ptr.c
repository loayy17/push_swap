/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:34:16 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:34:17 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_ptr(unsigned long long n, int fd)
{
	int	len;

	len = 0;
	if (n != '\0')
	{
		len += ft_dprintf_char('0', fd);
		len += ft_dprintf_char('x', fd);
		len += ft_dprintf_hex(n, fd);
		return (len);
	}
	len += write(fd, "(nil)", 5);
	return (len);
}
