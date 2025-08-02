/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:31:33 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/23 15:11:10 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_lstclear(t_free **lst)
{
	t_free	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->adr);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_lstadd_front(t_free **lst, t_free *new)
{
	if (!lst || !new)
		return ;
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	cleanup_and_exit(t_free **free_nodes, int status)
{
	if (free_nodes && *free_nodes)
		ft_lstclear(free_nodes);
	exit(status);
}

void	*ft_malloc(size_t size, t_free **free_nodes)
{
	t_free	*node;

	node = malloc(sizeof(t_free));
	if (!node)
	{
		print_error("Malloc failed");
		cleanup_and_exit(free_nodes, 1);
	}
	node->adr = malloc(size);
	if (!node->adr)
	{
		print_error("Malloc failed");
		cleanup_and_exit(free_nodes, 1);
	}
	node->next = NULL;
	ft_lstadd_front(free_nodes, node);
	return (node->adr);
}
