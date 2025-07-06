/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:32:49 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/06 10:11:29 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	floor_and_ceilling_valid(t_pop *vars)
{
	return (!ft_strcmp("F", &vars->str[vars->st])
		|| !ft_strcmp("C", &vars->str[vars->st]));
}

int	floor_and_ceilling(t_pop *vars, t_data *data, t_free **free_nodes)
{
	char	**strs;
	int		len;

	if ((!ft_strcmp(&vars->str[vars->st], "F") && data->floor)
		|| (!ft_strcmp(&vars->str[vars->st], "C") && data->ceilling))
		return (print_error("Duplicate color identifier"), 1);
	vars->str[vars->st + vars->en] = ' ';
	strs = ft_split_libft(vars->str, " \t\n\v\f\r", free_nodes);
	len = 0;
	while (strs[len])
		len++;
	if (len != 2)
		return (print_error("Invalid color format"), 1);
	vars->str[vars->st + vars->en] = '\0';
	if (!ft_strcmp("F", &vars->str[vars->st]))
	{
		if (parse_color(data, strs[1], free_nodes, 'F'))
			return (1);
	}
	else if (!ft_strcmp("C", &vars->str[vars->st]))
	{
		if (parse_color(data, strs[1], free_nodes, 'C'))
			return (1);
	}
	return (0);
}

int	is_texture_valid(t_pop *vars, t_data *data)
{
	char	*current;

	current = &vars->str[vars->st];
	if ((!ft_strcmp("NO", current) && !data->north)
		|| (!ft_strcmp("WE", current) && !data->west)
		|| (!ft_strcmp("EA", current) && !data->east)
		|| (!ft_strcmp("SO", current) && !data->south))
		return (1);
	return (0);
}

int	directions_populate(t_pop *vars, t_data *data, t_free **free_nodes)
{
	char	**strs;
	int		len;

	vars->str[vars->st + vars->en] = ' ';
	strs = ft_split_libft(vars->str, " \t\n\v\f\r", free_nodes);
	len = 0;
	while (strs[len])
		len++;
	if (len != 2 || check_ext(strs[1], ".xpm"))
		return (print_error("Invalid texture path format .xpm"), 1);
	if (strs[1] && !ft_strcmp("NO", strs[0]))
		data->north = strs[1];
	else if (strs[1] && !ft_strcmp("WE", strs[0]))
		data->west = strs[1];
	else if (strs[1] && !ft_strcmp("EA", strs[0]))
		data->east = strs[1];
	else if (strs[1] && !ft_strcmp("SO", strs[0]))
		data->south = strs[1];
	return (0);
}

int	redir_fds_init(t_data *data, char *arr[])
{
	arr[0] = data->north;
	arr[1] = data->south;
	arr[2] = data->west;
	arr[3] = data->east;
	return (1);
}

int	assign_redir_fds(t_data *data)
{
	int		fd_tmp;
	char	*arr[4];
	int		i;

	1 && (i = -1, redir_fds_init(data, arr));
	while (++i < 4)
	{
		if (!arr[i])
			return (print_error("Empty File"), 1);
		fd_tmp = open(arr[i], O_RDONLY, 0644);
		if (fd_tmp == -1)
			return (perror(arr[i]), 1);
		close(fd_tmp);
	}
	return (0);
}
