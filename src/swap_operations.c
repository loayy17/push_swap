/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <email@domain.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/04 21:30:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_node **s, char c, int both)
{
	t_node	*tmp;

	if (!*s || !(*s)->next)
		return ;
	tmp = *s;
	*s = (*s)->next;
	tmp->next = (*s)->next;
	(*s)->next = tmp;
	(*s)->prev = NULL;
	tmp->prev = *s;
	if (tmp->next)
		tmp->next->prev = tmp;
	if (!both)
		ft_printf("s%c\n", c);
}

void	push_stack(t_node **src, t_node **dst, char c, int not_print)
{
	t_node	*tmp;

	if (!*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	tmp->next = *dst;
	if (*dst)
		(*dst)->prev = tmp;
	*dst = tmp;
	if (!not_print)
		ft_printf("p%c\n", c);
}

void	rotate(t_node **s, char c, int both)
{
	t_node	*last;
	t_node	*tmp;

	if (!*s || !(*s)->next)
		return ;
	tmp = *s;
	last = *s;
	while (last->next)
		last = last->next;
	*s = (*s)->next;
	(*s)->prev = NULL;
	tmp->next = NULL;
	tmp->prev = last;
	last->next = tmp;
	if (!both)
		ft_printf("r%c\n", c);
}

void	reverse_rotate(t_node **s, char c, int both)
{
	t_node	*last;

	if (!*s || !(*s)->next)
		return ;
	last = *s;
	while (last->next)
		last = last->next;
	last->prev->next = NULL;
	last->prev = NULL;
	last->next = *s;
	(*s)->prev = last;
	*s = last;
	if (!both)
		ft_printf("rr%c\n", c);
}
