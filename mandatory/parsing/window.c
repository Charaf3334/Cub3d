/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:34:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/30 10:31:41 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int close_window_x(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	destroy_imgs(4, mlx);
	cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	return (0);
}

static void window_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1, handle_keypress, mlx);
	mlx_hook(mlx->win, 17, 0, close_window_x, mlx);
}

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x *
												  (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

<<<<<<< HEAD
int load_texture(void *mlx, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
=======
int	load_texture(void *mlx, t_texture *tex, char *path) 
{
    tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img)
>>>>>>> 620201e39a56e53ae5a5e9c833e11c2e74728471
	{
		print_error("Texture load failed");
		return (1);
	}
<<<<<<< HEAD
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
=======
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian); // line_len = width * 4 bytes | bpp = byte_per_pixel = 8 bits * 4 num_of_bytes = 32
>>>>>>> 620201e39a56e53ae5a5e9c833e11c2e74728471
	return (0);
}

void destroy_imgs(int index, t_mlx *mlx)
{
	void *arr[4];
	int i;

	i = 0;
	arr[0] = mlx->tex_north.img;
	arr[1] = mlx->tex_south.img;
	arr[2] = mlx->tex_west.img;
	arr[3] = mlx->tex_east.img;

	while (i < index)
		mlx_destroy_image(mlx->mlx, arr[i++]);
}

int init_textures(t_mlx *mlx, t_data *data)
{
	if (load_texture(mlx->mlx, &mlx->tex_north, data->north))
		return (1);
	if (load_texture(mlx->mlx, &mlx->tex_south, data->south))
		return (destroy_imgs(1, mlx), 1);
	if (load_texture(mlx->mlx, &mlx->tex_west, data->west))
		return (destroy_imgs(2, mlx), 1);
	if (load_texture(mlx->mlx, &mlx->tex_east, data->east))
		return (destroy_imgs(3, mlx), 1);
	return (0);
}

int window(t_data *data, t_free **free_nodes)
{
	t_mlx *mlx;

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
	mlx->addr = mlx_get_data_addr(mlx->img,
								  &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		return (mlx_destroy_image(mlx->mlx, mlx->img),
				mlx_destroy_window(mlx->mlx, mlx->win), 1);
	if (init_textures(mlx, data))
		return (mlx_destroy_image(mlx->mlx, mlx->img),
				mlx_destroy_window(mlx->mlx, mlx->win), 1);
	render(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	window_hooks(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
