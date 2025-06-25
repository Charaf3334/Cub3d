/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:36:11 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/25 10:45:11 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mandatory/cub3D.h"

int	is_sep(char ch, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (ch == c[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}
