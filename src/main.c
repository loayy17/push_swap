/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:50:34 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/04 23:44:55 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_stack(t_node **stack_a, t_node **stack_b)
{
	int	size;

	size = get_stack_size(*stack_a);
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else
		sort_large(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	if (argc < 2)
	{
		// ft_dprintf(2, "Error\n");
		return (1);
	}
	if (!validate_input(argv + 1))
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	stack_a = create_stack(argv + 1);
	if (!stack_a)
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	stack_b = NULL;
	if (!is_sorted(stack_a))
		sort_stack(&stack_a, &stack_b);
	free_resource(&stack_a, &stack_b);
	return (0);
}
