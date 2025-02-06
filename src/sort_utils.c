/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <email@domain.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/04 21:30:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_quicksort(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;
	int	temp;

	if (low < high)
	{
		pivot = low;
		i = low;
		j = high;
		while (i < j)
		{
			while (arr[i] <= arr[pivot] && i < high)
				i++;
			while (arr[j] > arr[pivot])
				j--;
			if (i < j)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
		temp = arr[pivot];
		arr[pivot] = arr[j];
		arr[j] = temp;
		ft_quicksort(arr, low, j - 1);
		ft_quicksort(arr, j + 1, high);
	}
}

int	count_below_pivot(t_node *stack, int pivot)
{
	int	count;

	count = 0;
	while (stack)
	{
		if (stack->data <= pivot)
			count++;
		stack = stack->next;
	}
	return (count);
}

int	find_position(t_node *stack, int value)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->data == value)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	ft_sqrt(int num)
{
	int	root;

	root = 1;
	while (root * root <= num)
		root++;
	return (root - 1);
}
int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}


