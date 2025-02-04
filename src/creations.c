/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Updated: 2025/02/03 02:44:45 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_node(char *data)
{
	t_node	*node;
	int		valid;

	node = malloc(sizeof(t_node));
	if (!node)
		return (0);
	valid = 1;
	node->data = (int)ft_atol_handle(data, &valid);
	node->next = NULL;
	node->prev = NULL;
	if (!valid)
	{
		free(node);
		return (0);
	}
	return (node);
}

t_node	*create_stack_a(char **str)
{
	t_node	*stack_a;
	t_node	*tail;
	t_node	*new_node;
	int		i;

	i = 0;
	stack_a = NULL;
	tail = NULL;
	while (str[i])
	{
		new_node = create_node(str[i]);
		if (!new_node)
		{
			cleanup_nodes(&stack_a);
			return (0);
		}
		if (!stack_a)
			stack_a = new_node;
		else
			tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
		i++;
	}
	return (stack_a);
}
