/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:16:30 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/30 13:53:58 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
 * assign_delta_x_y:
 *   Pre‑compute the length of one square step along X and Y for the DDA.
 *   A very large number (1e30) is used to approximate infinity when the
 *   ray direction component is zero to avoid division by zero.
 */

void assign_delta_x_y(t_ray *ray)
{
	if (!ray->ray_dir_x)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (!ray->ray_dir_y)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/*
 * init_ray_step_and_dist:
 *   Determine the direction to step (+1 or -1) in the map grid for both X
 *   and Y axes and compute the initial side distances to the first grid line.
 */

void init_ray_step_and_dist(t_ray *ray, t_data *data)
{
	/* X axis */
	if (ray->ray_dir_x < 0) // kichof fliser
	{
		ray->step_x = -1;													  // bach kanmovie ofo9iyan
		ray->side_dist_x = (data->player_x - ray->map_x) * ray->delta_dist_x; // delta_x lmorba3 lmasafa axis x
	}
	else // liman
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player_x) * ray->delta_dist_x;
	}

	/* Y axis */
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;													  // 3amodiyan
		ray->side_dist_y = (data->player_y - ray->map_y) * ray->delta_dist_y; // delta y //side_dist_y hiya lmasafa dyal lplayer mn lposition dyalo lawal carreau
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player_y) * ray->delta_dist_y;
	}
}

/*
 * init_ray:
 *   Build a new ray for screen column x:
 *   1. Compute direction from camera plane.
 *   2. Store player's current map cell.
 *   3. Precompute delta distances and initial side distances/steps.
 */

void init_ray(t_data *data, t_ray *ray, int x)
{
	float camera_x;

	/* camera_x ∈ [‑1, 1] maps pixel column to camera plane */
	camera_x = 2 * x / (float)WIDTH - 1;
	/* ray direction in world space */
	ray->ray_dir_x = data->dir_x + data->plane_x * camera_x;
	ray->ray_dir_y = data->dir_y + data->plane_y * camera_x;
	
	/* current grid square of the player */
	ray->map_x = (int)data->player_x;
	ray->map_y = (int)data->player_y;

	assign_delta_x_y(ray);			   // length of ray to next x/y side
	init_ray_step_and_dist(ray, data); // step direction & first side distance
	ray->hit = 0;					   // clear hit flag
}

/*
 * perform_dda:
 *   Classic Digital Differential Analyzer loop:
 *   Step from grid square to grid square along the ray until a wall ('1')
 *   is hit. After exiting, wall_dists the distance to the wall and
 *   ray->side indicates whether an X or Y side was hit (0 = X, 1 = Y).
 */

void perform_dda(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		/* Jump to next square in either X or Y direction */
		if (ray->side_dist_x < ray->side_dist_y) // ola dan lmasafa mabin position dlplayer o l7it fl x sgher mn lmasafa mabin position dlplayer o l7it fl y
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // hit came from an X side
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // hit came from an Y side
		}
		/* Check map: '1' denotes a wall */
		if (get_map_tile(data, ray->map_x, ray->map_y) == '1')
			ray->hit = 1;
	}

	/* Compute perpendicular wall distance to avoid fish‑eye effect */
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x; // distance mabin lplayer ol wall
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}
