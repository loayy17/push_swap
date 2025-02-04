/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:50:34 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/04 21:45:28 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
int get_stack_size(t_node *stack)
{
	int size;
	
	size = 0;
	while (stack)
	{
		stack = stack->next;
		size++;
	}
	return (size);
}
int get_min(t_node *stack)
{
	int min;
	if(!stack)
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

int get_max(t_node *stack)
{
	int max;
	if(!stack)
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

void sort_two(t_node **stack)
{
	if ((*stack)->data > (*stack)->next->data)
		swap(stack, 'a',0);
}

void	sort_three(t_node **stack)
{
	int	max;

	max = get_max(*stack);
	if ((*stack)->data == max)
	{
		rotate(stack, 'a',0);
		if (!is_sorted(*stack))
			swap(stack, 'a',0);
	}
	else if ((*stack)->next->data == max)
	{
		reverse_rotate(stack, 'a',0);
		if (!is_sorted(*stack))
			swap(stack, 'a',0);
	}
	else
	{
		if (!is_sorted(*stack))
			swap(stack, 'a',0);
	}
}

void sort_four(t_node **stack_a, t_node **stack_b)
{
	int i;
	int min;
	t_node *tmp;
	i = 0;
	while (i < 2)
	{
		min = get_min(*stack_a);
		tmp = *stack_a;
		while (tmp->data != min)
			tmp = tmp->next;
		if (tmp->data == min)
		{
			push_stack(stack_a, stack_b, 'b');
			i++;
		}
	}
	sort_three(stack_a);
	while (i--)
		push_stack(stack_b, stack_a, 'a');
}

void sort_five(t_node **stack_a, t_node **stack_b)
{
	int i;
	int min;
	t_node *tmp;
	i = 0;
	while (i < 2)
	{
		min = get_min(*stack_a);
		tmp = *stack_a;
		while (tmp->data != min)
			tmp = tmp->next;
		if (tmp->data == min)
		{
			push_stack(stack_a, stack_b, 'b');
			i++;
		}
	}
	sort_three(stack_a);
	while (i--)
		push_stack(stack_b, stack_a, 'a');
}

void sort_stack(t_node **stack_a, t_node **stack_b)
{
	int size;

	size = get_stack_size(*stack_a);
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, stack_b);
	else if (size == 5)
		sort_five(stack_a, stack_b);
	else
		sort_large(stack_a, stack_b);
}
int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	if (argc < 2 || !argv++)
	{
		ft_dprintf(2, "Usage: %s <Numbers>\n", argv[0]);
		return (1);
	}
	if (validate_input(argv))
		return (1);
	stack_a = create_stack_a(argv);
	if (!stack_a)
	{
		ft_dprintf(2, "Error: Memory Allocation Failed\n");
		return (1);
	}
	stack_b = NULL;
	sort_stack(&stack_a, &stack_b);
	free_resource(&stack_a, &stack_b);
	// ft_printf("Hello World\n");
	return (0);
}
