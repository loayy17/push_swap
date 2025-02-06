/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <email@domain.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/04 21:30:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_node(char *data)
{
	t_node	*node;
	int		valid;

	valid = 1;
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = ft_atol_handle(data, &valid);
	node->next = NULL;
	node->prev = NULL;
	node->pos = 0;
	if (!valid)
	{
		free(node);
		return (0);
	}
	return (node);
}

t_node	*create_stack(char **str)
{
	t_node	*stack;
	t_node	*tail;
	t_node	*new;
	int		i;

	stack = NULL;
	tail = NULL;
	i = 0;
	while (str[i])
	{
		new = create_node(str[i]);
		if (!new)
		{
			free_stack(&stack);
			return (0);
		}
		if (!stack)
			stack = new;
		else
			tail->next = new;
		new->prev = tail;
		tail = new;
		i++;
	}
	return (stack);
}

int	*create_sorted_array(t_node *stack)
{
	int	*arr;
	int	i;
	int	size;

	size = get_stack_size(stack);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (stack)
	{
		arr[i++] = stack->data;
		stack = stack->next;
	}
	ft_quicksort(arr, 0, size - 1);
	return (arr);
}

void	sort_two(t_node **stack)
{
	if (!*stack || !(*stack)->next)
		return ;
	if ((*stack)->data > (*stack)->next->data)
		swap(stack, 'a', 0);
}

void	sort_three(t_node **stack)
{
	int	max;

	if (!*stack || !(*stack)->next || !(*stack)->next->next)
		return ;
	max = get_max(*stack);
	if ((*stack)->data == max)
		rotate(stack, 'a', 0);
	if ((*stack)->next->data == max)
		reverse_rotate(stack, 'a', 0);
	if ((*stack)->data > (*stack)->next->data)
		swap(stack, 'a', 0);
}
