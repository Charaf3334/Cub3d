/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:37:04 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/15 11:04:52 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void render_3d_view(t_data *data) {
    for (int x = 0; x < WIDTH; x++) {
        t_ray ray;
        t_dda dda;
        
        init_ray(data, &ray, x);
        perform_dda(data, &ray);
        calculate_line(&ray, &dda);

        // Select texture based on wall direction
        t_texture *tex;
        if (ray.side == 0) 
            tex = (ray.step_x > 0) ? &data->mlx->tex_east : &data->mlx->tex_west;
        else 
            tex = (ray.step_y > 0) ? &data->mlx->tex_south : &data->mlx->tex_north;

        // Calculate wall hit position
        float wall_x = (ray.side == 0) 
            ? data->player_y + ray.perp_wall_dist * ray.ray_dir_y
            : data->player_x + ray.perp_wall_dist * ray.ray_dir_x;
        wall_x -= floor(wall_x);

        // Calculate texture X coordinate
        int tex_x = (int)(wall_x * tex->width);
        if (tex_x < 0)
            tex_x = 0;
        else if ((ray.side == 0 && ray.ray_dir_x > 0) || (ray.side == 1 && ray.ray_dir_y < 0))
            tex_x = tex->width - tex_x - 1;

        // Draw vertical texture stripe
        // float step = 1.0 * tex->height / dda.line_height;
        // float tex_pos = (dda.draw_start - HEIGHT/2.0 + dda.line_height/2.0) * step;
        
        // for (int y = dda.draw_start; y < dda.draw_end; y++) {
        //     int tex_y = (int)tex_pos;
        //     tex_pos += step;  // Always advance texture position
            
        //     // Clamp texture Y coordinate
        //     if (tex_y < 0)
        //         tex_y = 0;
        //     else if (tex_y >= tex->height)
        //         tex_y = tex->height - 1;
            
        //     // Get color from texture
        //     int color = *(int *)(tex->addr + 
        //                  (tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
            
        //     my_mlx_pixel_put(data->mlx, x, y, color);
        // }
		draw_ray(data, x, &dda, tex, tex_x);
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

