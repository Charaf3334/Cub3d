/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:34:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/31 15:30:43 by ctoujana         ###   ########.fr       */
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

int update_game(t_mlx *mlx)
{
	t_data *data = mlx->data;

	if (data->keys[W]) // W
		move_player(mlx, data->dir_x * MOVE_SPEED, data->dir_y * MOVE_SPEED);
	if (data->keys[S]) // S
		move_player(mlx, -data->dir_x * MOVE_SPEED, -data->dir_y * MOVE_SPEED);
	if (data->keys[A]) // A
		move_player(mlx, -data->dir_y * MOVE_SPEED, data->dir_x * MOVE_SPEED);
	if (data->keys[D]) // D
		move_player(mlx, data->dir_y * MOVE_SPEED, -data->dir_x * MOVE_SPEED);
	if (data->keys[LEFT_ARROW]) // Left arrow
		rotate_player(mlx, -0.05);
	if (data->keys[RIGHT_ARROW]) // Right arrow
		rotate_player(mlx, 0.05);
	render(mlx->data, mlx);
	return (0);
}

static void window_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1, handle_keypress, mlx);
	mlx_hook(mlx->win, 3, 2, handle_keyrelease, mlx);
	mlx_hook(mlx->win, 17, 0, close_window_x, mlx);
	mlx_loop_hook(mlx->mlx, update_game, mlx);
}

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_length + x *
												  (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int load_texture(void *mlx, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		print_error("Texture load failed");
		return (1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
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
	if (load_texture(mlx->mlx, &mlx->anim[0], "./textures/anim0.xpm"))
		return (destroy_imgs(4, mlx), 1);
	load_texture(mlx->mlx, &mlx->anim[1], "./textures/anim1.xpm");
	load_texture(mlx->mlx, &mlx->anim[2], "./textures/anim2.xpm");
	load_texture(mlx->mlx, &mlx->anim[3], "./textures/anim3.xpm");
	load_texture(mlx->mlx, &mlx->anim[4], "./textures/anim4.xpm");
	load_texture(mlx->mlx, &mlx->anim[5], "./textures/anim5.xpm");
	load_texture(mlx->mlx, &mlx->anim[6], "./textures/anim6.xpm");
	load_texture(mlx->mlx, &mlx->anim[7], "./textures/anim7.xpm");
	load_texture(mlx->mlx, &mlx->anim[8], "./textures/anim8.xpm");
	load_texture(mlx->mlx, &mlx->anim[9], "./textures/anim9.xpm");
	load_texture(mlx->mlx, &mlx->anim[10], "./textures/anim10.xpm");
	load_texture(mlx->mlx, &mlx->anim[11], "./textures/anim11.xpm");
	load_texture(mlx->mlx, &mlx->anim[12], "./textures/anim12.xpm");
	load_texture(mlx->mlx, &mlx->anim[13], "./textures/anim13.xpm");
	load_texture(mlx->mlx, &mlx->anim[14], "./textures/anim14.xpm");
	load_texture(mlx->mlx, &mlx->anim[15], "./textures/anim15.xpm");
	load_texture(mlx->mlx, &mlx->anim[16], "./textures/anim16.xpm");
	load_texture(mlx->mlx, &mlx->anim[17], "./textures/anim17.xpm");
	load_texture(mlx->mlx, &mlx->anim[18], "./textures/anim18.xpm");
	load_texture(mlx->mlx, &mlx->anim[19], "./textures/anim19.xpm");
	load_texture(mlx->mlx, &mlx->anim[20], "./textures/anim20.xpm");
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
