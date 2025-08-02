/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:47:14 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 15:10:08 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	data_populate(char *str, t_free **free_nodes, t_data *data)
{
	t_pop	vars;

	vars.st = 0;
	vars.en = 0;
	vars.str = str;
	while (vars.str[vars.st] && is_sep(vars.str[vars.st], " \t\n\v\f\r"))
		vars.st++;
	while (vars.str[vars.st + vars.en]
		&& !is_sep(vars.str[vars.st + vars.en], " \t\n\v\f\r"))
		vars.en++;
	vars.str[vars.st + vars.en] = '\0';
	if (is_texture_valid(&vars, data))
	{
		if (directions_populate(&vars, data, free_nodes))
			return (1);
	}
	else if (floor_and_ceilling_valid(&vars))
	{
		if (floor_and_ceilling(&vars, data, free_nodes))
			return (1);
	}
	else
		return (print_error("Unknown identifier"), 1);
	return (0);
}

int	populate_data(t_data *data, char *line, t_free **free_nodes, int *index)
{
	if (*index < 6)
	{
		if (line && line[0] == '\n')
			return (0);
		*index += 1;
		if (data_populate(line, free_nodes, data))
			return (1);
	}
	else
	{
		if (map_ll_populate(line, free_nodes, data))
			return (1);
	}
	return (0);
}

void	init_player_pos(t_data *data)
{
	int		i;
	int		y;
	t_map	*ll;

	ll = data->map_ll;
	y = 0;
	while (ll)
	{
		i = 0;
		while (ll->line[i])
		{
			if (ft_strchr("NSWE", ll->line[i]))
			{
				data->player_x = i + 0.5;
				data->player_y = y + 0.5;
				set_player_direction(data, ll->line[i]);
				ll->line[i] = '0';
			}
			i++;
		}
		y++;
		ll = ll->next;
	}
}

int	init_data_helper(t_data *data, int fd, char *line)
{
	if (assign_redir_fds(data))
		return (close(fd), 1);
	if (!data->map_ll)
		return (print_error("Empty map"), close(fd), 1);
	if (lltrim(&data->map_ll))
		return (print_error("Empty map"), close(fd), 1);
	if (check_map_valid(data))
		return (close(fd), 1);
	init_player_pos(data);
	get_next_line(-42);
	close(fd);
	if (!line)
		return (1);
	return (0);
}

int	init_data(t_data *data, char *file, t_free **free_nodes)
{
	int		fd;
	char	*line;
	int		index;

	index = 0;
	data->map_ll = NULL;
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		return (print_error("Invalid file"), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || !*line)
		{
			if (!line)
				return (print_error("Empty file"), close(fd), 1);
			else if (!*line)
				free(line);
			break ;
		}
		if (populate_data(data, line, free_nodes, &index))
			return (free(line), close(fd), 1);
		free(line);
	}
	return (init_data_helper(data, fd, line));
}
