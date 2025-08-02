/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:37:04 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 14:10:24 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	render_player(t_mlx *mlx)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = MINIMAP_SIZE / 2;
	player_y = MINIMAP_SIZE / 2;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			my_mlx_pixel_put(mlx, player_x + i, player_y + j, 0x0000FF);
			j++;
		}
		i++;
	}
}

static void	render_cross(t_mlx *mlx)
{
	int	middle_x;
	int	middle_y;
	int	i;

	i = -10;
	middle_x = WIDTH / 2;
	middle_y = HEIGHT / 2;
	while (i <= 13)
	{
		my_mlx_pixel_put(mlx, middle_x, middle_y + i, 0xFFFF00);
		my_mlx_pixel_put(mlx, middle_x + 1, middle_y + i, 0xFFFF00);
		my_mlx_pixel_put(mlx, middle_x + 2, middle_y + i, 0xFFFF00);
		my_mlx_pixel_put(mlx, middle_x + i, middle_y, 0xFFFF00);
		my_mlx_pixel_put(mlx, middle_x + i, middle_y + 1, 0xFFFF00);
		my_mlx_pixel_put(mlx, middle_x + i, middle_y + 2, 0xFFFF00);
		i++;
	}
}

static void	handle_animation_frames(t_mlx *mlx, int frame)
{
	int	div;
	int	pos_x;
	int	pos_y;

	if (WIDTH >= 1000 && WIDTH <= 1200)
		div = 2;
	if (WIDTH > 1200 && WIDTH <= 1400)
		div = 3;
	if (WIDTH > 1400 && WIDTH <= 1600)
		div = 4;
	if (WIDTH > 1600 && WIDTH <= 1920)
		div = 5;
	pos_x = (WIDTH / 2) - (mlx->anim[frame].width / div);
	pos_y = HEIGHT - mlx->anim[frame].height;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, \
		mlx->anim[frame].img, pos_x, pos_y);
}

void	handle_which_anim_frame(int *timer, int *frame, int *initialized)
{
	if (!(*initialized))
	{
		*timer = 0;
		*frame = 0;
		*initialized = 1;
	}
	if (++(*timer) >= 5)
	{
		*timer = 0;
		*frame = (*frame + 1) % ANIMATION_FRAMES;
	}
}

void	render(t_data *data, t_mlx *mlx)
{
	static int	timer;
	static int	frame;
	static int	initialized;
	int			flag;

	flag = 0;
	handle_which_anim_frame(&timer, &frame, &initialized);
	render_3d_view(data);
	render_minimap(data, mlx);
	render_player(mlx);
	render_cross(mlx);
	if (WIDTH >= 1000 && HEIGHT == 1080)
	{
		handle_animation_frames(mlx, frame);
		flag = 1;
	}
	if (!flag)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
