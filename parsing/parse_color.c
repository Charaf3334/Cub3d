/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:04:18 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/01 12:29:49 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	skip_zeroes(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	return (i);
}

int	process_color(char *color, int *num_out)
{
	int	num;

	if (color[0] == '\0')
		return (print_error("Empty color component not allowed"), 1);
	if (is_num(color))
		return (print_error("Color component must be digits only"), 1);
	if (ft_strlen(&color[skip_zeroes(color)]) > 3)
		return (print_error("Color component cannot exceed 255"), 1);
	num = ft_atoi(color);
	if (num > 255)
		return (print_error("Color component cannot exceed 255"), 1);
	*num_out = num;
	return (0);
}

void	set_color(t_data *data, char c, int index, int num)
{
	if (c == 'F')
	{
		if (index == 0)
			data->floor |= num << 16;
		else if (index == 1)
			data->floor |= num << 8;
		else if (index == 2)
			data->floor |= num;
	}
	else if (c == 'C')
	{
		if (index == 0)
			data->ceilling |= num << 16;
		else if (index == 1)
			data->ceilling |= num << 8;
		else if (index == 2)
			data->ceilling |= num;
	}
}

int	parse_color(t_data *data, char *str, t_free **free_nodes, char c)
{
	int		i;
	char	**strs;
	int		strs_len;
	int		num;

	if (ft_strlen(str) < 5)
		return (print_error("Len below 5"), 1);
	if (ft_strlen_char(str, ',') != 2)
		return (print_error("Invalid color format: need exactly 2 commas"), 1);
	strs = ft_split_libft(str, ",", free_nodes);
	strs_len = len_strs(strs);
	if (strs_len != 3)
		return (print_error("Invalid color: need exactly 3 components"), 1);
	i = 0;
	while (i < 3)
	{
		if (process_color(strs[i], &num))
			return (1);
		set_color(data, c, i, num);
		i++;
	}
	return (0);
}
