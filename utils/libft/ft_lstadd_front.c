/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:33:45 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/28 10:44:42 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mandatory/cub3D.h"

void	ft_lstadd_front(t_free **lst, t_free *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
