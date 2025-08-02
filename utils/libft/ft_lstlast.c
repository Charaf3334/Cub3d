/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:27:53 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/25 10:28:24 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

t_map	*ft_lstlast(t_map *lst)
{
	t_map	*node;

	if (!lst)
		return (NULL);
	node = lst;
	while (node->next != NULL)
		node = node->next;
	return (node);
}
