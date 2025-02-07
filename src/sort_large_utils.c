/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:12:03 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:38:17 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_from_a_to_b(t_node **a, t_node **b, int index, t_chunk *chunk)
{
	if (index < chunk->current * chunk->chunk_size
		|| chunk->current == chunk->total)
	{
		push_stack(a, b, 'b', 0);
		if (chunk->chunk_size > 1
			&& (*b)->data <= chunk->sorted[(chunk->current * chunk->chunk_size)
				- (chunk->chunk_size / 2)])
		{
			rotate(b, 'b', 0);
		}
	}
	else
	{
		if ((*a)->pos < get_stack_size(*a) / 2)
			rotate(a, 'a', 0);
		else
			reverse_rotate(a, 'a', 0);
	}
}

void	push_chunks(t_node **a, t_node **b, int *sorted, int size)
{
	t_chunk	chunk;
	int		index;

	chunk.size = size;
	chunk.total = dynamic_chunk_count(size);
	chunk.current = 1;
	chunk.chunk_size = size / chunk.total;
	if (chunk.chunk_size < 1)
		chunk.chunk_size = 1;
	chunk.sorted = sorted;
	while (get_stack_size(*a) > 3)
	{
		update_positions(*a);
		index = 0;
		while (index < chunk.size && sorted[index] != (*a)->data)
			index++;
		move_from_a_to_b(a, b, index, &chunk);
		if (get_stack_size(*b) >= chunk.current * chunk.chunk_size
			&& chunk.current < chunk.total)
			chunk.current++;
	}
}

int	get_target_position(t_node *a, int value)
{
	int		target;
	int		target_pos;
	t_node	*tmp;
	int		min;

	target = 2147483647;
	target_pos = -1;
	tmp = a;
	min = get_min(a);
	if (value < min || value > get_max(a))
		return (find_min_position(a));
	while (tmp)
	{
		if (tmp->data > value && tmp->data < target)
		{
			target = tmp->data;
			target_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	if (target_pos == -1)
		return (find_min_position(a));
	return (target_pos);
}

int	check_empty_b(t_node *b, int *ca, int *cb)
{
	if (!b)
	{
		*ca = 0;
		*cb = 0;
		return (1);
	}
	return (0);
}

void	update_best(t_node **a, t_node *tmp, t_move *move)
{
	int	cur[2];
	int	cost;

	cur[0] = get_target_position(*a, tmp->data);
	cur[1] = tmp->pos;
	if (cur[0] > move->sizes[0] / 2)
		cur[0] -= move->sizes[0];
	if (cur[1] > move->sizes[1] / 2)
		cur[1] -= move->sizes[1];
	cost = ft_abs(cur[0]) + ft_abs(cur[1]);
	if (cost < move->best_cost)
	{
		move->best[0] = cur[0];
		move->best[1] = cur[1];
		move->best_cost = cost;
	}
}
