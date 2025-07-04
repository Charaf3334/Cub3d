/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:42:00 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/04 11:06:01 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3D.h"

// Initialize ray for a given screen column
void	init_ray(t_data *data, t_ray *ray, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * camera_x;
	ray->ray_dir_y = data->dir_y + data->plane_y * camera_x;
	
	ray->map_x = (int)data->player_x;
	ray->map_y = (int)data->player_y;
	
	ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
	
	if (ray->ray_dir_x < 0) {
		ray->step_x = -1;
		ray->side_dist_x = (data->player_x - ray->map_x) * ray->delta_dist_x;
	} else {
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player_x) * ray->delta_dist_x;
	}
	
	if (ray->ray_dir_y < 0) {
		ray->step_y = -1;
		ray->side_dist_y = (data->player_y - ray->map_y) * ray->delta_dist_y;
	} else {
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player_y) * ray->delta_dist_y;
	}
	
	ray->hit = 0;
}

// Digital Differential Analysis (DDA) algorithm
void	perform_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0) {
		if (ray->side_dist_x < ray->side_dist_y) {
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		} else {
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		
		if (get_map_tile(data, ray->map_x, ray->map_y) == '1')
			ray->hit = 1;
	}
	
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

// Calculate line height and drawing positions
void	calculate_line(t_ray *ray, t_dda *dda)
{
	dda->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	dda->draw_start = -dda->line_height / 2 + HEIGHT / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = dda->line_height / 2 + HEIGHT / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT - 1;
}

// Draw the entire vertical column (ceiling, wall, floor)
void	draw_ray(t_data *data, int x, t_dda *dda, int color)
{
	int	y;

	y = 0;
	// Draw ceiling
	while (y < dda->draw_start)
	{
		my_mlx_pixel_put(data->mlx, x, y, data->ceilling);
		y++;
	}
	// Draw wall
	while (y <= dda->draw_end)
	{
		my_mlx_pixel_put(data->mlx, x, y, color);
		y++;
	}
	// Draw floor
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data->mlx, x, y, data->floor);
		y++;
	}
}

// Visualize the ray on the minimap
void	draw_ray_on_minimap(t_mlx *mlx, t_data *data, t_ray *ray)
{
	float	ray_x = data->player_x;
	float	ray_y = data->player_y;
	float	step = 0.05;
	float	dist = 0;
	
	while (dist < ray->perp_wall_dist && dist < 10) {
		ray_x += ray->ray_dir_x * step;
		ray_y += ray->ray_dir_y * step;
		
		int screen_x = (int)(ray_x * 20);
		int screen_y = (int)(ray_y * 20);
		
		if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT) {
			my_mlx_pixel_put(mlx, screen_x, screen_y, 0xFF00FF);
		}
		dist += step;
	}
}