/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:34:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/02 10:21:59 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	close_window_x(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	// mlx_destroy_display
	free(mlx->mlx);
	cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	return (0);
}

static int	close_window_esc(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		// mlx_destroy_display
		free(mlx->mlx);
		cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	}
	return (0);
}

static void	close_handle(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1, close_window_esc, mlx);
	mlx_hook(mlx->win, 17, 0, close_window_x, mlx);
}

int	window(t_data *data, t_free **free_nodes)
{
	t_mlx	*mlx;

	mlx = NULL;
	data->free_nodes = free_nodes;
	data->mlx = ft_malloc(sizeof(t_mlx), free_nodes);
	mlx = data->mlx;
	mlx->data = data;
	mlx->mlx = mlx_init(); // mlx_destroy_display
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, TITLE);
	if (!mlx->win)
		return (free(mlx->mlx), 1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (mlx_destroy_window(mlx->mlx, mlx->win), free(mlx->mlx), 1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		return (mlx_destroy_image(mlx->mlx, mlx->img), mlx_destroy_window(mlx->mlx, mlx->win), free(mlx->mlx), 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	close_handle(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
