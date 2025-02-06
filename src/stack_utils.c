/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <email@domain.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/04 21:30:00 by yourname         ###   ########.fr       */
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


void optimize_rotations(t_node **stack, int rotations)
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

void final_rotate(t_node **stack)
{
    int min_pos = find_position(*stack, get_min(*stack));
    int size = get_stack_size(*stack);
    int rotations = min_pos;

    if (min_pos > size / 2)
        rotations -= size;

    optimize_rotations(stack, rotations);
}
