/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:00:00 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/07 02:32:21 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_checker(t_node **a, t_node **b, char *instruction)
{
	free_resource(a, b);
	ft_dprintf(2, "Error\n");
	free(instruction);
	exit(1);
}

void	initial_stack_size(t_node **a, t_node **b, char **s, long *ss)
{
	*a = create_stack(s);
	*b = NULL;
	if (!*a)
	{
		ft_dprintf(2, "Error\n");
		exit(1);
	}
	*ss = get_stack_size(*a);
}

void	read_apply(t_node **a, t_node **b, char **l, long *ss)
{
	while (1)
	{
		*l = get_next_line(0);
		if (!*l)
			break ;
		(*l)[ft_strlen(*l) - 1] = '\0';
		execute_operation(a, b, *l);
		free(*l);
	}
	if (is_sorted(*a) && !(*b) && get_stack_size(*a) == *ss)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

void	execute_operation(t_node **a, t_node **b, char *ins)
{
	if (!ft_strcmp(ins, "pa"))
		push_stack(b, a, 'a', 1);
	else if (!ft_strcmp(ins, "pb"))
		push_stack(a, b, 'b', 1);
	else if (!ft_strcmp(ins, "ra"))
		rotate(a, 'a', 1);
	else if (!ft_strcmp(ins, "rb"))
		rotate(b, 'b', 1);
	else if (!ft_strcmp(ins, "rr"))
		rotate_both(a, b, 1);
	else if (!ft_strcmp(ins, "rra"))
		reverse_rotate(a, 'a', 1);
	else if (!ft_strcmp(ins, "rrb"))
		reverse_rotate(b, 'b', 1);
	else if (!ft_strcmp(ins, "rrr"))
		reverse_rotate_both(a, b, 1);
	else if (!ft_strcmp(ins, "sa"))
		swap(a, 'a', 1);
	else if (!ft_strcmp(ins, "sb"))
		swap(b, 'b', 1);
	else if (!ft_strcmp(ins, "ss"))
		swap_both(a, b, 1);
	else
		free_checker(a, b, ins);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	long	size_stack;
	char	*line;

	if (argc < 2)
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	if (!validate_input(argv + 1))
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	initial_stack_size(&stack_a, &stack_b, argv + 1, &size_stack);
	read_apply(&stack_a, &stack_b, &line, &size_stack);
	free_resource(&stack_a, &stack_b);
	return (0);
}
