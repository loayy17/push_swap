/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:26:56 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:26:56 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_number(int n)
{
	char	*a;
	int		len;

	len = 0;
	a = ft_itoa(n);
	len += ft_printf_string(a);
	free(a);
	return (len);
}
