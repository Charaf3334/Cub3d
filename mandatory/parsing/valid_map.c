/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:23:00 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 10:06:00 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	check_map_chars(char *line, int *flag)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	while (line[i])
	{
		if (is_sep(line[i], "NSWE"))
			(*flag)++;
		if (!is_sep(line[i], " 01NSWE\n"))
			return (1);
		i++;
	}
	return (0);
}

static int	validate_map_lines(t_map *head)
{
	int	i;
	int	j;

	j = 0;
	while (head)
	{
		i = 0;
		while (is_sep(head->line[i], " \t\n\v\f\r01NSWE"))
			i++;
		if (WIDTH < 200 || HEIGHT < 200)
		{
			print_error("The minimap tried to escape the screen!");
			return (1);
		}
		if (!head->next)
			break ;
		else if (!head->line[i])
			head = head->next;
		else
			return (print_error("Invalid map"), 1);
		j++;
	}
	if (!head)
		return (print_error("Invalid map"), 1);
	return (0);
}

int	check_map_valid(t_data *data)
{
	t_map	*current;
	int		player_count;

	if (validate_map_lines(data->map_ll))
		return (1);
	if (check_map_horiz_closed(data->map_ll))
		return (1);
	player_count = 0;
	current = data->map_ll;
	while (current)
	{
		if (check_map_chars(current->line, &player_count))
			return (print_error("Invalid character in map"), 1);
		if (player_count > 1)
			return (print_error("Too many players in map"), 1);
		current = current->next;
	}
	if (!player_count)
		return (print_error("No player found in map"), 1);
	if (check_map_vertic_closed(data->map_ll))
		return (1);
	return (0);
}
