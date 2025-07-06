/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:37:04 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/06 10:35:06 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	render_3d_view(t_data *data)
{
	int		x;
	int		color;
	t_ray	ray;
	t_dda	dda;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, &ray, x);
		perform_dda(data, &ray);
		calculate_line(&ray, &dda);
		
		// Determine wall direction for color
		if (ray.side == 0) // East/West walls
		{
			if (ray.step_x > 0)
				color = 0xFF0000; // East wall (Red)
			else
				color = 0xFFFF00; // West wall (Yellow)
		}
		else // North/South walls
		{
			if (ray.step_y > 0)
				color = 0x0000FF; // North wall (Blue)
			else
				color = 0x00FF00; // South wall (Green)
		}
		
		draw_ray(data, x, &dda, color);
		x++;
	}
}

static void	render_minimap(t_data *data, t_mlx *mlx)
{
	t_map	*map;
	int		y;
	int		x;
	int		i;
	int		color;

	map = data->map_ll;
	y = 0;
	while (map)
	{
		1 && (x = 0, i = 0);
		while (map->line[i])
		{
			if (map->line[i] == '0')
				color = 0xD2B48C; // Floor
			else if (map->line[i] == '1')
				color = 0x2F4F4F; // Wall
			else
				color = 0x000000; // Other
			draw_block(mlx, x * 20, y * 20, color);
			1 && (x++, i++);
		}
		y++;
		map = map->next;
	}
}

static void	render_player(t_data *data, t_mlx *mlx)
{
	int	player_x;
	int	player_y;
	int	i;
	int	j;

	player_x = (int)(data->player_x * 20);
	player_y = (int)(data->player_y * 20);
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

static void	render_direction_line(t_data *data, t_mlx *mlx)
{
	t_dir_line	line;
	int			i;
	float		x;
	float		y;

	line.player_x = (int)(data->player_x * 20);
	line.player_y = (int)(data->player_y * 20);
	line.dir_x = line.player_x + (int)(data->dir_x * 10);
	line.dir_y = line.player_y + (int)(data->dir_y * 10);
	line.dx = line.dir_x - line.player_x;
	line.dy = line.dir_y - line.player_y;
	line.steps = fmax(fabs(line.dx), fabs(line.dy));
	i = 0;
	while (i <= 30)
	{
		x = line.player_x + line.dx * (i / line.steps);
		y = line.player_y + line.dy * (i / line.steps);
		my_mlx_pixel_put(mlx, (int)x, (int)y, 0xFF0000);
		i++;
	}
}

static void	render_minimap_rays(t_data *data, t_mlx *mlx)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, &ray, x);
		perform_dda(data, &ray);
		draw_ray_on_minimap(mlx, data, &ray);
		x += 20;
	}
}
void	render(t_data *data, t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	ft_memset(mlx->addr, 0, HEIGHT * mlx->line_length);
	render_3d_view(data);
	render_minimap(data, mlx);
	render_player(data, mlx);
	render_direction_line(data, mlx);
	render_minimap_rays(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

