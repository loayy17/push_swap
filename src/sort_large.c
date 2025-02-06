/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/06 19:17:51 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	gcd(int a, int b)
{
    int t;
    
	while (b)
	{
		t = a % b;
		a = b;
		b = t;
	}
	return (a);
}

int	lcm(int a, int b)
{
	return ((a / gcd(a, b)) * b);
}

static int	dynamic_chunk_count(int size)
{
	int	base;
	if(size <= 10)
		return 1;
	else if(size <= 50)
		base = 2;
	else if (size <= 100)
		base = 1;
	else if (size <= 500)
		base = 5;
	else
		base = 22;
	return (base + (lcm(size, base) % 3));
}

static void	push_chunks(t_node **a, t_node **b, int *sorted, int size)
{
	int	chunks = dynamic_chunk_count(size);
	int	current_chunk = 1;
	int	chunk_size = size / chunks;
	if (chunk_size < 1)
		chunk_size = 1;
	while (get_stack_size(*a) > 3)
	{
		update_positions(*a);
		int index = 0;
		while (index < size && sorted[index] != (*a)->data)
			index++;
		if (index < current_chunk * chunk_size || current_chunk == chunks)
		{
			push_stack(a, b, 'b',0);
			int threshold = current_chunk * chunk_size - (chunk_size / 2);
			if (threshold < 0)
				threshold = 0;
			if ((*b)->data <= sorted[threshold])
				rotate(b, 'b', 0);
		}
		else
		{
			if ((*a)->pos < get_stack_size(*a) / 2)
				rotate(a, 'a', 0);
			else
				reverse_rotate(a, 'a', 0);
		}
		if (get_stack_size(*b) >= current_chunk * chunk_size && current_chunk < chunks)
			current_chunk++;
	}
}

static int	get_target_position(t_node *a, int value)
{
	int		pos = 0;
	int		target = 2147483647;
	int		target_pos = -1;
	t_node	*tmp = a;
	int		min = get_min(a);

	if (value < min || value > get_max(a))
		return (find_min_position(a));
	while (tmp)
	{
		if (tmp->data > value && tmp->data < target)
		{
			target = tmp->data;
			target_pos = tmp->pos;
		}
		pos++;
		tmp = tmp->next;
	}
	return (target_pos == -1 ? find_min_position(a) : target_pos);
}

static void	calculate_move(t_node **a, t_node **b, int *ca, int *cb)
{
	t_node	*tmp = *b;
	int		best[2];
	int		cur[2];
	int		sizes[2];
	int		best_cost;

	sizes[0] = get_stack_size(*a);
	sizes[1] = get_stack_size(*b);
	if (!(*b))
	{
		*ca = 0;
		*cb = 0;
		return ;
	}
	update_positions(*a);
	update_positions(*b);
	best[0] = get_target_position(*a, tmp->data);
	best[1] = tmp->pos;
	if (best[0] > sizes[0] / 2)
		best[0] -= sizes[0];
	if (best[1] > sizes[1] / 2)
		best[1] -= sizes[1];
	best_cost = ft_abs(best[0]) + ft_abs(best[1]);
	tmp = tmp->next;
	while (tmp)
	{
		cur[0] = get_target_position(*a, tmp->data);
		cur[1] = tmp->pos;
		if (cur[0] > sizes[0] / 2)
			cur[0] -= sizes[0];
		if (cur[1] > sizes[1] / 2)
			cur[1] -= sizes[1];
		if ((ft_abs(cur[0]) + ft_abs(cur[1])) < best_cost)
		{
			best[0] = cur[0];
			best[1] = cur[1];
			best_cost = ft_abs(cur[0]) + ft_abs(cur[1]);
		}
		tmp = tmp->next;
	}
	*ca = best[0];
	*cb = best[1];
}

static void	execute_rotations(t_node **a, t_node **b, int ca, int cb)
{
	while (ca > 0 && cb > 0)
	{
		rotate_both(a, b,0);
		ca--;
		cb--;
	}
	while (ca < 0 && cb < 0)
	{
		reverse_rotate_both(a, b,0);
		ca++;
		cb++;
	}
	while (ca > 0)
	{
		rotate(a, 'a', 0);
		ca--;
	}
	while (ca < 0)
	{
		reverse_rotate(a, 'a', 0);
		ca++;
	}
	while (cb > 0)
	{
		rotate(b, 'b', 0);
		cb--;
	}
	while (cb < 0)
	{
		reverse_rotate(b, 'b', 0);
		cb++;
	}
}

void	sort_large(t_node **a, t_node **b)
{
	int		*sorted;
	int		size;
	int		cost[2];

	size = get_stack_size(*a);
	sorted = create_sorted_array(*a);
	if (!sorted)
		return ;
	push_chunks(a, b, sorted, size);
	while (get_stack_size(*a) > 3)
		push_stack(a, b, 'b',0);
	sort_three(a);
	while (*b)
	{
		update_positions(*a);
		update_positions(*b);
		calculate_move(a, b, &cost[0], &cost[1]);
		execute_rotations(a, b, cost[0], cost[1]);
		push_stack(b, a, 'a',0);
	}
	final_rotate(a);
	free(sorted);
}
