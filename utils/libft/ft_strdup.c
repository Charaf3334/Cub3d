/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:43:36 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 13:29:45 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

char	*ft_strdup_normal(char *str, t_free **free_nodes)
{
	char	*new;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str);
	new = ft_malloc(len + 1, free_nodes);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
