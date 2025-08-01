/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:38:59 by ctoujana          #+#    #+#             */
/*   Updated: 2025/08/01 13:39:26 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	close_window_x(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	destroy_imgs(4, mlx);
	destroy_animations(ANIMATION_FRAMES, mlx);
	cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	return (0);
}

int	update_game(t_mlx *mlx)
{
	t_data	*data;

	data = mlx->data;
	if (data->keys[W])
		move_player(mlx, data->dir_x * MOVE_SPEED, data->dir_y * MOVE_SPEED);
	if (data->keys[S])
		move_player(mlx, -data->dir_x * MOVE_SPEED, -data->dir_y * MOVE_SPEED);
	if (data->keys[A])
		move_player(mlx, -data->dir_y * MOVE_SPEED, data->dir_x * MOVE_SPEED);
	if (data->keys[D])
		move_player(mlx, data->dir_y * MOVE_SPEED, -data->dir_x * MOVE_SPEED);
	if (data->keys[LEFT_ARROW])
		rotate_player(mlx, -ROTATE_ANGLE);
	if (data->keys[RIGHT_ARROW])
		rotate_player(mlx, ROTATE_ANGLE);
	render(mlx->data, mlx);
	return (0);
}

void	window_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1, handle_keypress, mlx);
	mlx_hook(mlx->win, 3, 2, handle_keyrelease, mlx);
	mlx_hook(mlx->win, 17, 0, close_window_x, mlx);
	mlx_loop_hook(mlx->mlx, update_game, mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	load_texture(void *mlx, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		print_error("Texture load failed");
		return (1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		print_error("Texture load failed");
		return (1);
	}
	return (0);
}
