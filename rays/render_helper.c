/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:01:18 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 15:34:21 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	tex_which_side(t_render *vars, t_data *data)
{
	if (vars->ray.side == 0)
	{
		if (vars->ray.step_x > 0)
			vars->tex = &data->mlx->tex_east;
		else
			vars->tex = &data->mlx->tex_west;
	}
	else
	{
		if (vars->ray.step_y > 0)
			vars->tex = &data->mlx->tex_south;
		else
			vars->tex = &data->mlx->tex_north;
	}
	if (vars->ray.side == 0)
		vars->wall_x = data->player_y + vars->ray.wall_dist \
			* vars->ray.ray_dir_y;
	else
		vars->wall_x = data->player_x + vars->ray.wall_dist \
			* vars->ray.ray_dir_x;
	vars->wall_x = vars->wall_x - floor(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * vars->tex->width);
}

void	render_3d_view(t_data *data)
{
	int			x;
	t_render	vars;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(data, &vars.ray, x);
		perform_dda(data, &vars.ray);
		calculate_line(&vars.ray, &vars.dda);
		tex_which_side(&vars, data);
		draw_ray(data, x, &vars.dda, &vars);
		x++;
	}
}

char	minimap_get_tile(int map_y, int map_x, t_map *map)
{
	int		row;
	char	tile;

	row = 0;
	tile = ' ';
	while (map && row < map_y)
	{
		map = map->next;
		row++;
	}
	if (map && map_x >= 0 && map_x < (int)ft_strlen(map->line))
		tile = map->line[map_x];
	return (tile);
}

void	render_minimap(t_data *data, t_mlx *mlx)
{
	t_minimap	vars;
	t_map		*map;

	vars.start_x = data->player_x - 5;
	vars.start_y = data->player_y - 5;
	map = data->map_ll;
	vars.y = -1;
	while (++vars.y < 100)
	{
		vars.x = -1;
		while (++vars.x < 100)
		{
			vars.map_x = (int)floorf(vars.start_x + \
				(vars.x / (float)10));
			vars.map_y = (int)floorf(vars.start_y + \
				(vars.y / (float)10));
			vars.tile = minimap_get_tile(vars.map_y, vars.map_x, map);
			if (ft_strchr("0SNEW", vars.tile))
				vars.color = 0xA3C9A8;
			else if (vars.tile == '1')
				vars.color = 0x2D3142;
			else
				vars.color = 0xBFC0C0;
			my_mlx_pixel_put(mlx, vars.x, vars.y, vars.color);
		}
	}
}
