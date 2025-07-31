/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:22:20 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/31 09:51:30 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_player_direction(t_data *data, char direction)
{
	if (direction == 'N')
	{
		data->player_dir = M_PI / 2;
		data->dir_x = 0; //cos(M_PI / 2)
		data->dir_y = -1; //sin(M_PI / 2)
	}
	else if (direction == 'S')
	{
		data->player_dir = 3 * M_PI / 2;
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (direction == 'W')
	{
		data->player_dir = M_PI;
		data->dir_x = -1;
		data->dir_y = 0;
	}
	else if (direction == 'E')
	{
		data->player_dir = 0;
		1 && (data->dir_x = 1, data->dir_y = 0);
	}
	// Set camera plane perpendicular to direction
	data->plane_x = -data->dir_y * 0.66;
	data->plane_y = data->dir_x * 0.66;
}