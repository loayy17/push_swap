/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:01:02 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/07 00:03:05 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	gcd(int a, int b)
{
	int	t;

	while (b)
	{
		t = a % b;
		a = b;
		b = t;
	}
	return (a);
}

int	lcm(int a, int b)
{
	return ((a / gcd(a, b)) * b);
}

int	get_min(t_node *stack)
{
	int	min;

	if (!stack)
		return (0);
	min = stack->data;
	while (stack)
	{
		if (stack->data < min)
			min = stack->data;
		stack = stack->next;
	}
	return (min);
}

int	get_max(t_node *stack)
{
	int	max;

	if (!stack)
		return (0);
	max = stack->data;
	while (stack)
	{
		if (stack->data > max)
			max = stack->data;
		stack = stack->next;
	}
	return (max);
}

int	dynamic_chunk_count(int size)
{
	int	base;

	if (size <= 10)
		return (1);
	else if (size <= 50)
		base = 2;
	else if (size <= 100)
		base = 1;
	else if (size <= 500)
		base = 5;
	else
		base = 22;
	return (base + (lcm(size, base) % 3));
}
