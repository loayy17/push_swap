/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:30:19 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/08 00:30:19 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_llist;
	t_list	*new_element;
	void	*content;

	if (!lst)
		return (NULL);
	new_llist = NULL;
	while (lst)
	{
		content = (*f)(lst->content);
		new_element = ft_lstnew(content);
		if (!new_element)
		{
			if (content)
				del(content);
			ft_lstclear(&new_llist, del);
			return (NULL);
		}
		ft_lstadd_back(&new_llist, new_element);
		lst = lst->next;
	}
	return (new_llist);
}
