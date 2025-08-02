/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:55:50 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 14:05:47 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_player(t_mlx *mlx, float dx, float dy)
{
	t_data	*data;
	float	new_x;
	float	new_y;

	data = mlx->data;
	new_x = data->player_x + dx;
	new_y = data->player_y + dy;
	if (get_map_tile(data, (int)(new_x), (int)data->player_y) != '1')
		data->player_x = new_x;
	if (get_map_tile(data, (int)data->player_x, (int)(new_y)) != '1')
		data->player_y = new_y;
}

static void	rotate_right_angle(t_data *data)
{
	if (data->dir_x > 0.999)
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	else if (data->dir_x < -0.999)
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
	if (data->dir_y > 0.999)
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (data->dir_y < -0.999)
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
}

void	rotate_player(t_mlx *mlx, float angle)
{
	t_data	*data;
	float	old_dir_x;
	float	old_plane_x;

	data = mlx->data;
	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	// Rotate direction vector
	// cos(0.1)  0.99 | sin(0.1)  0.099 
	// cos(-0.1) 0.99 | sin(-0.1) -0.099
	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	rotate_right_angle(data);
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
}

int	handle_keyrelease(int keycode, t_mlx *mlx)
{
	if (keycode >= 0 && keycode < 256)
		mlx->data->keys[keycode] = 0;
	return (0);
}

int	handle_keypress(int keycode, t_mlx *mlx)
{
	if (keycode >= 0 && keycode < 256)
		mlx->data->keys[keycode] = 1;
	if (keycode == ESC)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		destroy_imgs(4, mlx);
		destroy_animations(ANIMATION_FRAMES, mlx);
		cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	}
	return (0);
}
