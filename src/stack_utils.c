/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:36:54 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:36:56 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_stack_size(t_node *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

void	update_positions(t_node *stack)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		stack->pos = pos;
		pos++;
		stack = stack->next;
	}
}

int	find_min_position(t_node *a)
{
	int		min;
	int		pos;
	t_node	*tmp;

	min = get_min(a);
	pos = 0;
	tmp = a;
	while (tmp)
	{
		if (tmp->data == min)
			return (pos);
		pos++;
		tmp = tmp->next;
	}
	return (0);
}

void	optimize_rotations(t_node **stack, int rotations)
{
	if (rotations > 0)
	{
		while (rotations > 0)
		{
			rotate(stack, 'a', 0);
			rotations--;
		}
	}
	else
	{
		while (rotations < 0)
		{
			reverse_rotate(stack, 'a', 0);
			rotations++;
		}
	}
}

void	final_rotate(t_node **stack)
{
	int	min_pos;
	int	size;
	int	rotations;

	min_pos = find_min_position(*stack);
	size = get_stack_size(*stack);
	rotations = min_pos;
	if (min_pos > size / 2)
		rotations -= size;
	optimize_rotations(stack, rotations);
}
