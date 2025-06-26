/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_horiz_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:35:13 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/26 17:28:13 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_trimmed_bounds(char *line, int *start, int *end)
{
	*start = 0;
	*end = ft_strlen(line) - 1;
	while (line[*start] && is_sep(line[*start], " \t\n\v\f\r"))
		(*start)++;
	if (line[*start] == '\0')
		return (1);
	while (*end >= 0 && is_sep(line[*end], " \t\n\v\f\r"))
		(*end)--;
	if (*end < 0)
		return (1);
	return (0);
}

static int	validate_internal_spaces(char *line, int start, int end)
{
	int	i;
	int	j;

	i = start;
	while (i <= end)
	{
		if (line[i] == ' ')
		{
			j = i;
			while (j <= end && line[j] == ' ')
				j++;
			if (i == start || j > end)
				return (1);
			if (line[i - 1] != '1' || line[j] != '1')
				return (1);
			i = j;
		}
		else
			i++;
	}
	return (0);
}

static int	check_in_between(t_map *head)
{
	int		start;
	int		end;
	t_map	*curr;

	curr = head;
	if (get_trimmed_bounds(curr->line, &start, &end))
		return (1);
	if (curr->line[start] != '1' || curr->line[end] != '1')
		return (1);
	return (validate_internal_spaces(curr->line, start, end));
}

static int	check_closed_first_last(char *line)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(line) - 1;
	while (line[start] && is_sep(line[start], " \t\n\v\f\r"))
		start++;
	if (line[start] == '\0')
		return (1);
	while (end >= 0 && is_sep(line[end], " \t\n\v\f\r"))
		end--;
	while (start <= end)
	{
		if (line[start] != '1' && line[start] != ' ')
			return (1);
		start++;
	}
	return (0);
}

int	check_map_horiz_closed(t_map *head)
{
	int		i;
	t_map	*curr;

	i = 0;
	curr = head;
	if (!curr)
		return (print_error("Empty map"), 1);
	//horinzontal done
	while (curr)
	{
		if (i == 0 || !curr->next)// First or last line
		{
			if (check_closed_first_last(curr->line))
				return (printf("line1: |%s|\n", curr->line), print_error("Map not closed"), 1);
		}
		else// Middle lines
		{
			if (check_in_between(curr))
				return (printf("line[%d]: |%s|\n", i, curr->line), print_error("Map not closed"), 1);
		}
		curr = curr->next;
		i++;
	}
	return (0);
}
