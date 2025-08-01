/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:55:50 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/01 13:48:25 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_player(t_mlx *mlx, float dx, float dy)
{
	t_data	*data;
	float	new_x;
	float	new_y;

	data = mlx->data;
	new_x  = data->player_x + dx;
	new_y = data->player_y + dy;
	// Check collision in X direction
	if (get_map_tile(data, (int)(new_x), (int)data->player_y) != '1')
		data->player_x = new_x;
	// Check collision in Y direction
	if (get_map_tile(data, (int)data->player_x, (int)(new_y)) != '1')
		data->player_y = new_y;
}

void	rotate_player(t_mlx *mlx, float angle)
{
	t_data	*data;
	float	old_dir_x;
	float	old_plane_x;

	data = mlx->data;
	old_dir_x = data->dir_x; //tmp values
	old_plane_x = data->plane_x;
	// Rotate direction vector
	// cos(0.1) 0.99 | sin(0.1) 0.099 
	// printf("before:\ndir_x %f | dir_y %f\n", data->dir_x, data->dir_y);

	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	
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
	
	// Rotate camera plane
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
	// Update player direction angle
	data->player_dir += angle;
	// Normalize angle between 0 and 2π
	// if (data->player_dir < 0) // hadi lach asln kayna hh
	// 	data->player_dir += 2 * M_PI;
	// if (data->player_dir > 2 * M_PI)
	// 	data->player_dir -= 2 * M_PI;
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
