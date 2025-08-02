/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:31:05 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 13:29:45 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	check(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	start;
	int	end;

	if (s1 == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (check(s1[start], set))
		start++;
	while (check(s1[end], set))
		end--;
	return (ft_substr(s1, start, (end - start) + 1));
}
