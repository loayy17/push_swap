/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/07 01:52:17 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	initialize_best(t_node **a, t_node *b, t_move *move)
{
	move->best[0] = get_target_position(*a, b->data);
	move->best[1] = b->pos;
	if (move->best[0] > move->sizes[0] / 2)
		move->best[0] -= move->sizes[0];
	if (move->best[1] > move->sizes[1] / 2)
		move->best[1] -= move->sizes[1];
	move->best_cost = ft_abs(move->best[0]) + ft_abs(move->best[1]);
}

static void	calculate_move(t_node **a, t_node **b, int *ca, int *cb)
{
	t_node	*tmp;
	t_move	move;

	update_positions(*a);
	update_positions(*b);
	if (check_empty_b(*b, ca, cb))
		return ;
	move.sizes[0] = get_stack_size(*a);
	move.sizes[1] = get_stack_size(*b);
	tmp = *b;
	initialize_best(a, tmp, &move);
	tmp = tmp->next;
	while (tmp)
	{
		update_best(a, tmp, &move);
		tmp = tmp->next;
	}
	*ca = move.best[0];
	*cb = move.best[1];
}

void	execute_both_rotations(t_node **a, t_node **b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		rotate_both(a, b, 0);
		(*ca)--;
		(*cb)--;
	}
	while (*ca < 0 && *cb < 0)
	{
		reverse_rotate_both(a, b, 0);
		(*ca)++;
		(*cb)++;
	}
}

static void	execute_rotations(t_node **a, t_node **b, int ca, int cb)
{
	execute_both_rotations(a, b, &ca, &cb);
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
	int	*sorted;
	int	size;
	int	cost[2];

	size = get_stack_size(*a);
	sorted = create_sorted_array(*a);
	if (!sorted)
		return ;
	push_chunks(a, b, sorted, size);
	while (get_stack_size(*a) > 3)
		push_stack(a, b, 'b', 0);
	sort_three(a);
	while (*b)
	{
		update_positions(*a);
		update_positions(*b);
		calculate_move(a, b, &cost[0], &cost[1]);
		execute_rotations(a, b, cost[0], cost[1]);
		push_stack(b, a, 'a', 0);
	}
	final_rotate(a);
	free(sorted);
}
