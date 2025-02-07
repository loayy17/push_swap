/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:30:59 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:30:59 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*buffer1;
	unsigned char	*buffer2;

	i = len;
	buffer1 = (unsigned char *)src;
	buffer2 = (unsigned char *)dst;
	if (dst == src)
		return (dst);
	else if (buffer2 > buffer1)
	{
		while (i-- > 0)
			*(buffer2 + i) = *(buffer1 + i);
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*(buffer2 + i) = *(buffer1 + i);
			i++;
		}
	}
	return (buffer2);
}
