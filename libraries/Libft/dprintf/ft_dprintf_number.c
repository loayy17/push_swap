/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:34:11 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:34:12 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintf_number(int n, int fd)
{
	char	*a;
	int		len;

	len = 0;
	a = ft_itoa(n);
	len += ft_dprintf_string(a, fd);
	free(a);
	return (len);
}
