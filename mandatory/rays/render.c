/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:37:04 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 09:35:43 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	render_3d_view(t_data *data)
{
	int			x;
	t_render	vars;

	x = 0;
    while (x < WIDTH)
	{
        init_ray(data, &vars.ray, x);
        perform_dda(data, &vars.ray);
        calculate_line(&vars.ray, &vars.dda);
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
		if (vars.ray.side == 0)
			vars.wall_x = data->player_y + vars.ray.wall_dist * vars.ray.ray_dir_y; // wall_x : howa coordinate bdept fin drb ray f dak grid '1' li howa l7it 
		else
			vars.wall_x = data->player_x + vars.ray.wall_dist * vars.ray.ray_dir_x;

		
        vars.wall_x -= floor(vars.wall_x); // it was floor(vars.wall_x)
		// Calculate texture X coordinate
		vars.tex_x = (int)(vars.wall_x * vars.tex->width);
		
		// so tex_x hia column dyal texture mnin atbda trsm tal tex_y ... 
		
		
		
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


static void render_minimap(t_data *data, t_mlx *mlx)
{
	float	start_x;
	float	start_y;
	float	world_x;
	float	world_y;
	int		map_x;
	int		map_y;
	int		y;
	int		x;
	int		color;
	int		row;
	t_map	*map;
	char	tile;

	start_x = data->player_x - MINI_RADIUS;
	start_y = data->player_y - MINI_RADIUS;
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			world_x = start_x + (x / (float)MINI_SCALE);
			world_y = start_y + (y / (float)MINI_SCALE);
			map_x = (int)floorf(world_x);
			map_y = (int)floorf(world_y);
			map = data->map_ll;
			row = 0;
			while (map && row < map_y)
			{
				map = map->next;
				row++;
			}
			if (map && map_x >= 0 && map_x < (int)ft_strlen(map->line))
				tile = get_map_tile(data, map_x, map_y);
			if (ft_strchr("0SNEW", tile))
				color = 0xD2B48C;
			else if (tile == '1')
				color = 0x2F4F4F;
			else
				color = 0x000000;
			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

static void	render_player(t_data *data, t_mlx *mlx)
{
	(void)data;
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


static void	render_cross(t_data *data, t_mlx *mlx)
{
	(void) data;
	int	middle_x;
	int	middle_y;
	int	i;
	int	j;

	middle_x = WIDTH / 2;
	middle_y = HEIGHT / 2;
	i = -10;
	while (i <= 10)
	{
		j = -10;
		while (j <= 13)
		{
			my_mlx_pixel_put(mlx, middle_x, middle_y + j, 0xFFFF00);
			my_mlx_pixel_put(mlx, middle_x + 1, middle_y + j, 0xFFFF00);
			my_mlx_pixel_put(mlx, middle_x + 2, middle_y + j, 0xFFFF00);
			j++;
		}
		i++;
	}
	i = -10;
	while (i <= 13)
	{
		j = -10;
		while (j <= 10)
		{
			my_mlx_pixel_put(mlx, middle_x + i, middle_y, 0xFFFF00);
			my_mlx_pixel_put(mlx, middle_x + i, middle_y + 1, 0xFFFF00);
			my_mlx_pixel_put(mlx, middle_x + i, middle_y + 2, 0xFFFF00);
			j++;
		}
		i++;
	}
}

// static void	render_direction_line(t_data *data, t_mlx *mlx)
// {
// 	t_dir_line	line;
// 	int			i;
// 	float		x;
// 	float		y;

// 	line.player_x = (int)(data->player_x * 20);
// 	line.player_y = (int)(data->player_y * 20);
// 	line.dir_x = line.player_x + (int)(data->dir_x * 10);
// 	line.dir_y = line.player_y + (int)(data->dir_y * 10);
// 	line.dx = line.dir_x - line.player_x;
// 	line.dy = line.dir_y - line.player_y;
// 	line.steps = fmax(fabs(line.dx), fabs(line.dy));
// 	i = 0;
// 	while (i <= 30)
// 	{
// 		x = line.player_x + line.dx * (i / line.steps);
// 		y = line.player_y + line.dy * (i / line.steps);
// 		my_mlx_pixel_put(mlx, (int)x, (int)y, 0xFF0000);
// 		i++;
// 	}
// }

// static void	render_minimap_rays(t_data *data, t_mlx *mlx)
// {
// 	int		x;
// 	t_ray	ray;

// 	x = (MINIMAP_SIZE / 2);
// 	init_ray(data, &ray, x);
// 	perform_dda(data, &ray);
// 	draw_ray_on_minimap(mlx, data, &ray);
// }

void	render(t_data *data, t_mlx *mlx)
{
	static int	timer;
	static int	frame;
	static int	initialized;
	int			pos_x;
	int			pos_y;

	if (!initialized)
	{
		timer = 0;
		frame = 0;
		initialized = 1;
	}
	if (++timer >= 5)
	{
		timer = 0;
		frame = (frame + 1) % ANIMATION_FRAMES;
	}
	render_3d_view(data);
	render_minimap(data, mlx);
	render_player(data, mlx);
	// render_minimap_rays(data, mlx);
	render_cross(data, mlx);
	pos_x = (WIDTH / 2) - (mlx->anim[frame].width / 12);
	pos_y = HEIGHT - mlx->anim[frame].height;	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->anim[frame].img, pos_x, pos_y);
}
