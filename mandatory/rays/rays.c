/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:42:00 by zguellou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/30 10:08:42 by zguellou         ###   ########.fr       */
=======
/*   Updated: 2025/07/28 14:52:26 by ctoujana         ###   ########.fr       */
>>>>>>> 620201e39a56e53ae5a5e9c833e11c2e74728471
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
 * calculate_line:
 *   Given the perpendicular wall distance for a ray, compute the height of the
 *   vertical stripe that will be drawn on the screen and its start/end pixel
 *   positions. Values are clamped to the screen bounds.
 */

void calculate_line(t_ray *ray, t_dda *dda)
{
	// l3bar dl7it, bachma kan wall dist sghir bachma kan l3bar dl7it kbir
	if (ray->wall_dist < 0.000001) // ola kan lmap sghir, wall dist katwelli zero, and when we divide by zero, wa7ed number 3imla9 kikhrej o segfaulti
		ray->wall_dist = 0.000001;
	dda->line_height = (int)(HEIGHT / ray->wall_dist);

	// Top pixel (start) of the wall slice depart dl7it
	dda->draw_start = HEIGHT / 2 - dda->line_height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;

	// Bottom pixel (end) of the wall slice
	dda->draw_end = HEIGHT / 2 + dda->line_height / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT - 1;
}

/*
 * draw_ray:
 *   Paint a single vertical stripe at screen column x.
 *   - Sky/ceiling from y = 0 to draw_start - 1 (color: data->ceilling)
 *   - Wall slice from draw_start to draw_end (color: 'color' argument)
 *   - Floor from draw_end + 1 to bottom of screen (color: data->floor)
 */

void draw_ray(t_data *data, int x, t_dda *dda, t_render *vars)
{
	int y;
	float step;
	float tex_pos;
	int tex_y;
	int color;

	y = 0;
	while (y < dda->draw_start)
	{
		my_mlx_pixel_put(data->mlx, x, y, data->ceilling);
		y++;
	}

	// height = 600
	// line_height = 200
	// draw_start = 200

	// tex_pos = (dda->draw_start - HEIGHT / 2.0 + dda->line_height / 2.0) * step;
	
	// 1. Center of the screen vertically
	float screen_center = HEIGHT / 2.0; // center = 300

	// 2. Center of the wall on screen
	float wall_center = dda->line_height / 2.0; // center = 100

	// 3. Vertical offset from screen center to where wall starts
	float distance_from_center_to_start = dda->draw_start - screen_center; // 200 - 300 = -100

	// 4. So now shift texture starting point by how far wall is from center
	// This aligns the wall texture center to the wall slice on screen
	float texture_start_offset = (distance_from_center_to_start + wall_center); // -100 + 100 = 0

	// step = 1 * 64 / 200 = 0.32
	step = 1.0 * vars->tex->height / dda->line_height; // for each pixel on screen, move step pixels down in the texture
	
	// 5. Multiply by 'step' to get actual texture coordinate (float)
	tex_pos = texture_start_offset * step;

	while (y <= dda->draw_end)
	{
		tex_y = (int)tex_pos; // we convert to integer to fetch the pixel
		tex_pos += step;  // Step by the ratio of texture_height / line_height
		
		// Clamp texture Y coordinate : hadi protection bach matkhrjch mn pixels dyal texture, katb9a tdor f range [0, tex->height - 1];
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= vars->tex->height)
			tex_y = vars->tex->height - 1;
		// Get color from texture
		color = *(int *)(vars->tex->addr +
						 (tex_y * vars->tex->line_len + vars->tex_x * (vars->tex->bpp / 8)));
		my_mlx_pixel_put(data->mlx, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data->mlx, x, y, data->floor);
		y++;
	}
}

/*
 * draw_ray_on_minimap:
 *   Visualizes the active ray on the minimap by stepping along the ray
 *   direction in small increments (vars.step) until either the perpendicular
 *   wall distance is reached or a maximum length (10 units) is exceeded.
 *   Each intermediate point is plotted with a magenta pixel (0xFF00FF).
 */

void draw_ray_on_minimap(t_mlx *mlx, t_data *data, t_ray *ray)
{
	t_draw_ray vars;

	/* Start at the player's position */
	vars.ray_x = data->player_x;
	vars.ray_y = data->player_y;

	vars.step = 0.05; // world‑space step size
	vars.dist = 0;
	while (vars.dist < ray->wall_dist && vars.dist < 10)
	{
		/* advance along the ray */
		vars.ray_x += ray->ray_dir_x * vars.step;
		vars.ray_y += ray->ray_dir_y * vars.step;

		/* convert world coordinates to minimap pixels (scale ×20) */
		vars.screen_x = (int)(vars.ray_x * 20);
		vars.screen_y = (int)(vars.ray_y * 20);

		/* plot if inside the window */
		if (vars.screen_x >= 0 && vars.screen_x < WIDTH && vars.screen_y >= 0 && vars.screen_y < HEIGHT)
			my_mlx_pixel_put(mlx, vars.screen_x, vars.screen_y, 0xFFFF00);
		vars.dist += vars.step;
	}
}
