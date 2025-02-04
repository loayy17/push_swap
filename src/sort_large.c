/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Description: Implements a chunk-based quick sort algorithm           */
/*                using only the allowed operations.                        */
/*   Updated: 2025/02/04 21:xx:xx by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static int	compare_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

void	sort_large(t_node **stack_a, t_node **stack_b)
{
	int		size;
	int		*sorted;
	t_node	*tmp;
	int		i;
	int		chunk_count;
	int		chunk_size;
	int		current_chunk;
	int		mid_index;
	size = get_stack_size(*stack_a);
	sorted = malloc(sizeof(int) * size);
	if (!sorted)
		return ;
	tmp = *stack_a;
	i = 0;
	while (tmp)
	{
		sorted[i++] = tmp->data;
		tmp = tmp->next;
	}
	qsort(sorted, size, sizeof(int), compare_int);
	if (size <= 100)
		chunk_count = 5;
	else
		chunk_count = 11;
	chunk_size = size / chunk_count;
	current_chunk = 1;
	while (*stack_a)
	{
		int	value = (*stack_a)->data;
		int	index = 0;
		while (index < size && sorted[index] != value)
			index++;
		if (index < current_chunk * chunk_size || (current_chunk == chunk_count))
		{
			push_stack(stack_a, stack_b, 'b');
			mid_index = ((current_chunk - 1) * chunk_size) + (chunk_size / 2);
			if (*stack_b && (*stack_b)->data < sorted[mid_index])
				rotate(stack_b, 'b',0);
		}
		else
			rotate(stack_a, 'a',0);

		if (get_stack_size(*stack_b) == current_chunk * chunk_size && current_chunk < chunk_count)
			current_chunk++;
	}

	free(sorted);

	// 4. Push back from b to a in sorted order.
	while (*stack_b)
	{
		int max = get_max(*stack_b);
		int pos = 0;
		int size_b = get_stack_size(*stack_b);
		tmp = *stack_b;
		while (tmp)
		{
			if (tmp->data == max)
				break ;
			pos++;
			tmp = tmp->next;
		}
		if (pos <= size_b / 2)
		{
			while ((*stack_b)->data != max)
				rotate(stack_b, 'b',0);
		}
		else
		{
			while ((*stack_b)->data != max)
				reverse_rotate(stack_b, 'b',0);
		}
		push_stack(stack_b, stack_a, 'a');
	}
}
