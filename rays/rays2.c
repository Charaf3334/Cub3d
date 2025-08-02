/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:16:30 by ctoujana          #+#    #+#             */
/*   Updated: 2025/08/02 14:08:56 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	assign_delta_x_y(t_ray *ray)
{
	if (ray->ray_dir_x)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_ray_step_and_dist(t_ray *ray, t_data *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player_x) \
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player_y) * \
			ray->delta_dist_y;
	}
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * camera_x; //[-0.66, 0.66] cos(angle) = -0.66
	ray->ray_dir_y = data->dir_y + data->plane_y * camera_x; //-1
	ray->map_x = (int)data->player_x;
	ray->map_y = (int)data->player_y;
	assign_delta_x_y(ray);
	init_ray_step_and_dist(ray, data);
	ray->hit = 0;
}

void	perform_dda(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (get_map_tile(data, ray->map_x, ray->map_y) == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}
