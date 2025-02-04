/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:39:10 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/04 21:39:48 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_node **stack, char a,int both)
{
	t_node	*first_node;
	t_node	*second_node;

	if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
		return ;
	first_node = *stack;
	second_node = first_node->next;
	first_node->next = second_node->next;
	first_node->prev = second_node;
	second_node->next = first_node;
	second_node->prev = NULL;
	*stack = second_node;
	if (a == 'a' && !both)
		ft_printf("sa\n");
	else if(a == 'b' && !both)
		ft_printf("sb\n");
}

void	push_stack(t_node **src, t_node **dest, char c)
{
	t_node	*tmp;

	if (!src || !*src)
		return ;
	tmp = *src;
	*src = tmp->next;
	if (*src)
		(*src)->prev = NULL;
	tmp->next = *dest;
	if (*dest)
		(*dest)->prev = tmp;
	*dest = tmp;
	tmp->prev = NULL;
	if (c == 'a')
		ft_printf("pa\n");
	else
		ft_printf("pb\n");
}

void	rotate(t_node **stack, char c,int both)
{
	t_node	*tmp;
	t_node	*last_node;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	last_node = tmp;
	while (last_node->next)
		last_node = last_node->next;
	*stack = tmp->next;
	(*stack)->prev = NULL;
	tmp->next = NULL;
	tmp->prev = last_node;
	last_node->next = tmp;
	if (c == 'a' && !both)
		ft_printf("ra\n");
	else if (c == 'b' && !both)
		ft_printf("rb\n");
}

void	reverse_rotate(t_node **stack, char c,int both)
{
	t_node	*tmp;
	t_node	*last_node;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	last_node = tmp;
	while (last_node->next)
		last_node = last_node->next;
	last_node->prev->next = NULL;
	last_node->next = tmp;
	tmp->prev = last_node;
	last_node->prev = NULL;
	*stack = last_node;
	if (c == 'a' && !both)
		ft_printf("rra\n");
	else if(c == 'b' && !both)
		ft_printf("rrb\n");
}
