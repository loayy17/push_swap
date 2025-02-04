/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Updated: 2025/02/04 20:23:54 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_both(t_node **stack_a, t_node **stack_b)
{
	swap(stack_a, 'a',1);
	swap(stack_b, 'b',1);
	ft_printf("ss\n");
}

void	rotate_both(t_node **stack_a, t_node **stack_b)
{
	rotate(stack_a, 'a',1);
	rotate(stack_b, 'b',1);
	ft_printf("rr\n");
}

void	reverse_rotate_both(t_node **stack_a, t_node **stack_b)
{
	reverse_rotate(stack_a, 'a',1);
	reverse_rotate(stack_b, 'b',1);
	ft_printf("rrr\n");
}
