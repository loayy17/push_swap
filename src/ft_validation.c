/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Updated: 2025/02/04 21:13:48 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_all_number(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_number(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->data > stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	ft_is_duplicated(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_strcmp(str[i], str[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_input(char **str)
{
	if (!ft_is_all_number(str))
	{
		ft_dprintf(2, "Error: Invalid Input\n");
		return (1);
	}
	if (ft_is_duplicated(str))
	{
		ft_dprintf(2, "Error: Duplicated Numbers\n");
		return (1);
	}
	if (is_sorted(create_stack_a(str)))
	{
		ft_printf("Already Sorted\n");
		return (1);
	}
	return (0);
}
