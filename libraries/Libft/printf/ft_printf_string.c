/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:27:11 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:27:11 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_string(char *args)
{
	int	length;

	length = 0;
	if (args == NULL)
		return (write(1, "(null)", 6));
	while (args[length] != '\0')
	{
		write(1, &args[length], 1);
		length++;
	}
	return (length);
}
