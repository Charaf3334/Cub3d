/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:34:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/08/01 13:38:40 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	destroy_imgs(int index, t_mlx *mlx)
{
	void	*arr[4];
	int		i;

	i = 0;
	arr[0] = mlx->tex_north.img;
	arr[1] = mlx->tex_south.img;
	arr[2] = mlx->tex_west.img;
	arr[3] = mlx->tex_east.img;
	while (i < index)
		mlx_destroy_image(mlx->mlx, arr[i++]);
}

void	destroy_animations(int index, t_mlx *mlx)
{
	while (--index >= 0)
		mlx_destroy_image(mlx->mlx, mlx->anim[index].img);
}

int	init_textures(t_mlx *mlx, t_data *data)
{
	int		i;
	char	*path;
	char	*index;

	i = 0;
	if (load_texture(mlx->mlx, &mlx->tex_north, data->north))
		return (1);
	if (load_texture(mlx->mlx, &mlx->tex_south, data->south))
		return (destroy_imgs(1, mlx), 1);
	if (load_texture(mlx->mlx, &mlx->tex_west, data->west))
		return (destroy_imgs(2, mlx), 1);
	if (load_texture(mlx->mlx, &mlx->tex_east, data->east))
		return (destroy_imgs(3, mlx), 1);
	while (i < ANIMATION_FRAMES)
	{
		index = ft_itoa(i);
		path = ft_strjoin3("./textures/anim", index, ".xpm", data->free_nodes);
		if (load_texture(mlx->mlx, &mlx->anim[i], path))
			return (free(index), destroy_imgs(4, mlx),
				destroy_animations(i, mlx), 1);
		free(index);
		i++;
	}
	return (0);
}

void	render_and_hooks(t_data *data, t_mlx *mlx)
{
	render(data, mlx);
	window_hooks(mlx);
}

int	window(t_data *data, t_free **free_nodes)
{
	t_mlx	*mlx;

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
	render_and_hooks(data, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
