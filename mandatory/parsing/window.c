/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:34:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/15 11:46:24 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	close_window_x(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	return (0);
}

static void	window_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1, handle_keypress, mlx);
	mlx_hook(mlx->win, 17, 0, close_window_x, mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * \
	(mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void load_texture(void *mlx, t_texture *tex, char *path) {
    tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img)
	{
        print_error("Texture load failed");
		exit(1);
	}
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
}

void init_textures(t_mlx *mlx, t_data *data) {
    load_texture(mlx->mlx, &mlx->tex_north, data->north);
    load_texture(mlx->mlx, &mlx->tex_south, data->south);
    load_texture(mlx->mlx, &mlx->tex_west, data->west);
    load_texture(mlx->mlx, &mlx->tex_east, data->east);
}

int	window(t_data *data, t_free **free_nodes)
{
	t_mlx	*mlx;

	mlx = NULL;
	data->mlx = ft_malloc(sizeof(t_mlx), free_nodes);
	mlx = data->mlx;
	mlx->data = data;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, TITLE);
	if (!mlx->win)
		return (1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (mlx_destroy_window(mlx->mlx, mlx->win), 1);
	mlx->addr = mlx_get_data_addr(mlx->img, \
	&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		return (mlx_destroy_image(mlx->mlx, mlx->img), \
		mlx_destroy_window(mlx->mlx, mlx->win), 1);
	init_textures(mlx, data);
	render(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	window_hooks(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
