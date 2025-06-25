/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:41:44 by zguellou          #+#    #+#             */
/*   Updated: 2024/11/15 11:41:46 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*new_content;
	t_list	*new_list;
	t_list	*node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	node = NULL;
	while (lst != NULL)
	{
		node = ft_lstnew(NULL);
		if (!node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_content = f(lst->content);
		node->content = new_content;
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}
