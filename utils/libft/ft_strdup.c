/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:43:36 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/23 14:12:23 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mandatory/cub3D.h"

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
