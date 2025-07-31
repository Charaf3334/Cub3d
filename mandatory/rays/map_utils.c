/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:59:00 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/31 10:40:58 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"

char	get_map_tile(t_data *data, int x, int y)
{
	int		i;
	t_map	*row;

	row = data->map_ll;
	i = 0;
	while (i < y && row)
	{
		row = row->next;
		i++;
	}
	if (!row || x < 0 || x >= (int)ft_strlen(row->line))
		return ('1'); // Treat out-of-bounds as wall
	return (row->line[x]);
}

void	draw_block(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			my_mlx_pixel_put(mlx, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
