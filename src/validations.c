/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:37:05 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:37:06 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_duplicates(char **str)
{
	int		i;
	int		j;
	int		valid;
	long	number;
	long	number_new;

	i = -1;
	while (str[++i])
	{
		j = i;
		number = ft_atol_handle(str[i], &valid);
		if (!valid)
			return (1);
		while (str[++j])
		{
			number_new = ft_atol_handle(str[j], &valid);
			if (!valid)
				return (1);
			if (number == number_new)
				return (1);
		}
	}
	return (0);
}

int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->data > stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	validate_input(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!is_valid_number(str[i]))
			return (0);
		i++;
	}
	if (check_duplicates(str))
		return (0);
	return (1);
}
