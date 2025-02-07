/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:34:06 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:34:07 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_hex(unsigned long n, int fd)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_dprintf_hex(n / 16, fd);
		len += ft_dprintf_hex(n % 16, fd);
	}
	else
		len += write(fd, &"0123456789abcdef"[n], 1);
	return (len);
}
// 254 => fe
// int main()
// {
//     unsigned long num = 254;
//     int length = printf_hex(num);
//     write(1, "\n", 1);
//     write(1, "Number of characters printed: ", 30);
//     char buffer[20];
//     int len = sprintf(buffer, "%d\n", length);
//     write(1, buffer, len);
//     return (0);
// }