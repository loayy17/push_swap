/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/06 23:27:52 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_both(t_node **stack_a, t_node **stack_b,int both)
{
	swap(stack_a, 'a', !both);
	swap(stack_b, 'b', !both);
	if(!both)
		ft_printf("ss\n");
}

void	rotate_both(t_node **a, t_node **b,int both)
{
	if (*a && (*a)->next && *b && (*b)->next)
	{
		rotate(a, 'a', !both);
		rotate(b, 'b', !both);
		if(!both)
			ft_printf("rr\n");
	}
}

void	reverse_rotate_both(t_node **a, t_node **b, int both)
{
	if (*a && (*a)->next && *b && (*b)->next)
	{
		reverse_rotate(a, 'a', 1);
		reverse_rotate(b, 'b', 1);
		if(!both)
			ft_printf("rrr\n");
	}
}

void	free_stack(t_node **stack)
{
	t_node	*tmp;

	while (*stack)
	{
		tmp = (*stack);
		*stack = (*stack)->next;
		free(tmp);
	}
}

void	free_resource(t_node **stack_a, t_node **stack_b)
{
	if (stack_a && *stack_a)
		free_stack(stack_a);
	if (stack_b && *stack_b)
		free_stack(stack_b);
}
