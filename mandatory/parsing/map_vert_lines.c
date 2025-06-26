/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_vert_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:10:08 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/26 17:28:17 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	handle_previous_lines(t_map *curr, int i)
{
	t_map *prev;

	prev = curr->prev;
	if (!prev || !prev->line || !prev->line[i])
		return (1);
	while (prev)
	{
		if (prev->line[i] == '1')
			return (0);
		else if (prev->line[i] == ' ')
			return (1);
		prev = prev->prev;
	}
	return (1);
}

static int	handle_next_lines(t_map *curr, int i)
{
	t_map *next;

	next = curr->next;
	if (!next || !next->line || !next->line[i])
		return (1);
	while (next)
	{
		if (next->line[i] == '1')
			return (0);
		else if (next->line[i] == ' ')
			return (1);
		next = next->next;
	}
	return (1);
}

int	check_map_vertic_closed(t_map *head)
{
	int		i;
	t_map	*curr;

	i = 0;
	curr = head;
	//vertical
	while (curr)
	{
		i = 0;
		while (curr->line[i])
		{
			while (curr->line[i] && !is_sep(curr->line[i], "0WSEN"))
				i++;
			if (!curr->line[i])
				break ;
			if (handle_previous_lines(curr, i))
				return (printf("vertic line[%d]: |%s|\n", i, curr->line), print_error("Unclosed map fo9"), 1);
			if (handle_next_lines(curr, i))
				return (printf("vertic line[%d]: |%s|\n", i, curr->line), print_error("Unclosed map lte7t"), 1);
			i++;
		}
		curr = curr->next;
		i++;
	}
	return (0);
}
