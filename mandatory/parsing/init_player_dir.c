/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:22:20 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 10:49:51 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_player_direction(t_data *data, char direction)
{
	if (direction == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1; //sin 3pi / 2
	}
	else if (direction == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (direction == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
	else if (direction == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	data->plane_x = -data->dir_y * 0.66;
	data->plane_y = data->dir_x * 0.66;
}
