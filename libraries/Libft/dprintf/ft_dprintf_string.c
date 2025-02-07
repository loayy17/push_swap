/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:34:21 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:34:22 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_string(char *args, int fd)
{
	int	length;

	length = 0;
	if (args == NULL)
		return (write(fd, "(null)", 6));
	while (args[length] != '\0')
	{
		write(fd, &args[length], 1);
		length++;
	}
	return (length);
}
