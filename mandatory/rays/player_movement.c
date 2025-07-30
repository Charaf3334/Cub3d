/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:55:50 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/30 10:22:01 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	move_player(t_mlx *mlx, float dx, float dy)
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

static void rotate_player(t_mlx *mlx, float angle)
{
	t_data	*data;
	float	old_dir_x;
	float	old_plane_x;

	data = mlx->data;
	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	// Rotate direction vector
	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	// Rotate camera plane
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
	// Update player direction angle
	data->player_dir += angle;
	// Normalize angle between 0 and 2π
	if (data->player_dir < 0)
		data->player_dir += 2 * M_PI;
	if (data->player_dir > 2 * M_PI)
		data->player_dir -= 2 * M_PI;
}
// Update the key handling in handle_keypress
int	handle_keypress(int keycode, t_mlx *mlx)
{
	t_data	*data;

	data = mlx->data;
	if (keycode == 53) // ESC
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		destroy_imgs(4, mlx);
		cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	}
	else if (keycode == 13) // W - Move forward in facing direction
		move_player(mlx, data->dir_x * MOVE_SPEED, data->dir_y * MOVE_SPEED);
	else if (keycode == 1)  // S - Move backward
		move_player(mlx, -data->dir_x * MOVE_SPEED, -data->dir_y * MOVE_SPEED);
	else if (keycode == 2)  // A - Strafe left
		move_player(mlx, -data->dir_y * MOVE_SPEED, data->dir_x * MOVE_SPEED);
	else if (keycode == 0)  // D - Strafe right
		move_player(mlx, data->dir_y * MOVE_SPEED, -data->dir_x * MOVE_SPEED);
	else if (keycode == 124) // right arrow
		rotate_player(mlx, 0.1); // Rotate right
	else if (keycode == 123) // left arrow
		rotate_player(mlx, -0.1); // Rotate left
	render(mlx->data, mlx);
	return (0);
}

