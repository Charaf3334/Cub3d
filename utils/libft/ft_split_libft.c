/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:14:10 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 13:29:45 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	is_sep1(char ch, char *c)
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

static	int	ft_count_words(char *str, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_sep1(str[i], c))
			i++;
		if (str[i] == '\0')
			break ;
		count++;
		while (str[i] && !is_sep1(str[i], c))
			i++;
	}
	return (count);
}

static char	*ft_word_maker(char *str, int *index, char *c, t_free **free_nodes)
{
	char	*word;
	int		i;
	int		len;
	int		j;

	i = *index;
	len = 0;
	j = 0;
	while (str[i] && is_sep1(str[i], c))
		i++;
	while (str[i + len] && !is_sep1(str[i + len], c))
		len++;
	word = ft_malloc(sizeof(char) * (len + 1), free_nodes);
	while (j < len)
		word[j++] = str[i++];
	word[j] = '\0';
	*index = i;
	return (word);
}

char	**ft_split_libft(char *str, char *c, t_free **free_nodes)
{
	char	**split;
	int		i;
	int		index;
	int		len;

	if (str == NULL)
		return (NULL);
	i = 0;
	index = 0;
	len = ft_count_words(str, c);
	split = ft_malloc(sizeof(char *) * (len + 1), free_nodes);
	while (i < len)
		split[i++] = ft_word_maker(str, &index, c, free_nodes);
	split[i] = NULL;
	return (split);
}
