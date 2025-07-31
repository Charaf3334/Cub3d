/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:37:04 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/31 12:46:52 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void render_3d_view(t_data *data)
{
	int			x;
	t_render	vars;

	x = 0;
    while (x < WIDTH)
	{
        init_ray(data, &vars.ray, x);
        perform_dda(data, &vars.ray);
        calculate_line(&vars.ray, &vars.dda);

        // Select texture based on wall direction
        if (vars.ray.side == 0)
		{
			if (vars.ray.step_x > 0)
				vars.tex = &data->mlx->tex_east;
			else
				vars.tex = &data->mlx->tex_west;
		}
        else
		{
			if (vars.ray.step_y > 0)
				vars.tex = &data->mlx->tex_south;
			else
				vars.tex = &data->mlx->tex_north;
		}

        // Calculate wall hit position
		if (vars.ray.side == 0)
			vars.wall_x = data->player_y + vars.ray.wall_dist * vars.ray.ray_dir_y;
		else
			vars.wall_x = data->player_x + vars.ray.wall_dist * vars.ray.ray_dir_x;
        vars.wall_x -= floor(vars.wall_x); // it was floor(vars.wall_x)
		// Calculate texture X coordinate
		vars.tex_x = (int)(vars.wall_x * vars.tex->width);
		// printf("tex_x: %d\n", vars.tex_x);
		// so ila mchina mea mital li 9bl, wall_x howa 0.72, so aykhsna n7wlo hadchi l pixel column f texture, so lakan width howa 100, 72% dyalha hia column 72;
		
		// had code t7tani galik kadiro bach mtkonch lek texture m9loba, tkhrbi9 w sf hh 
		// if (vars.tex_x < 0)
		// 	vars.tex_x = 0;
		// else if ((vars.ray.side == 0 && vars.ray.ray_dir_x > 0) || (vars.ray.side == 1 && vars.ray.ray_dir_y < 0))
		// 	vars.tex_x = vars.tex->width - vars.tex_x - 1;
		draw_ray(data, x, &vars.dda, &vars);
		x++;
	}
}

int s = 0;

static void	render_minimap(t_data *data, t_mlx *mlx)
{
	t_map	*map;
	unsigned long		y;
	unsigned long		x;
	int		i;
	int		color;

	map = data->map_ll;
	y = 0;
	while (map)
	{
		1 && (x = 0, i = 0);
		while (map->line[i])
		{
			sleep(20);
			if (1 || x * 20 >= WIDTH || y * 20 >= HEIGHT)
			{
				print_error("The minimap tried to escape the screen!");
				mlx_destroy_image(mlx->mlx, mlx->img);
				mlx_destroy_window(mlx->mlx, mlx->win);
				destroy_imgs(4, mlx);
				cleanup_exit(data, data->free_nodes, 1);
			}
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

	x = WIDTH / 2;
	init_ray(data, &ray, x);
	perform_dda(data, &ray);
	draw_ray_on_minimap(mlx, data, &ray);
}

void	render(t_data *data, t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	ft_memset(mlx->addr, 0, HEIGHT * mlx->line_length);
	render_3d_view(data);
	render_minimap(data, mlx);
	render_player(data, mlx);
	// render_direction_line(data, mlx);
	render_minimap_rays(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

