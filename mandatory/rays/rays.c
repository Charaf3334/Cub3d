/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:42:00 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 11:33:24 by ctoujana         ###   ########.fr       */
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
	int		y;
	float	step;
	float	tex_starting_pos;
	int		tex_y;
	int		color;

	y = 0;
	while (y < dda->draw_start)
	{
		my_mlx_pixel_put(data->mlx, x, y, data->ceilling);
		y++;
	}

	// 1. Calculate how many texture pixels to skip for each screen pixel
	// If wall is tall on screen, step is small; if wall is short, step is big
	step = (1.0 * vars->tex->height) / dda->line_height;

	// 2. Calculate how far the top of the wall slice is from the center of the screen
	// We use this to know where to start reading from the texture
	float tex_start_offset_on_wall = dda->draw_start - (HEIGHT / 2.0) + (dda->line_height / 2.0);

	// 3. Multiply by step to find the starting position inside the texture
	// This aligns the center of the wall texture with the center of the wall slice on screen
	tex_starting_pos = tex_start_offset_on_wall * step;

	// 4. Draw the vertical wall slice
	while (y <= dda->draw_end)
	{
		// Convert float texture position to an integer texture row (Y)
		tex_y = (int)tex_starting_pos;

		// Protect against out-of-bounds texture access (just in case)
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= vars->tex->height)
			tex_y = vars->tex->height - 1;

		// Get the color from the texture at (tex_x, tex_y)
		// tex_x is fixed (the column of the texture we want)
		// tex_y is changing as we move down the screen
		color = *(int *)(vars->tex->addr +
							(tex_y * vars->tex->line_len + vars->tex_x * (vars->tex->bpp / 8)));

		// Draw pixel to screen
		my_mlx_pixel_put(data->mlx, x, y, color);

		// Move to the next position in the texture for the next screen pixel
		tex_starting_pos += step;
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
	vars.ray_x = data->player_x - MINI_RADIUS;
	vars.ray_y = data->player_y - MINI_RADIUS;

	vars.step = 0.05; // world‑space step size
	vars.dist = 0;
	while (vars.dist < ray->wall_dist && vars.dist < 10)
	{
		/* advance along the ray */
		vars.ray_x += ray->ray_dir_x * vars.step;
		vars.ray_y += ray->ray_dir_y * vars.step;

		/* convert world coordinates to minimap pixels (scale ×20) */
		vars.screen_x = (int)(vars.ray_x * MINIMAP_SIZE / 2);
		vars.screen_y = (int)(vars.ray_y * MINIMAP_SIZE / 2);

		/* plot if inside the window */
		if (vars.screen_x >= 0 && vars.screen_x < WIDTH && vars.screen_y >= 0 && vars.screen_y < HEIGHT)
			my_mlx_pixel_put(mlx, vars.screen_x, vars.screen_y, 0xFFFF00);
		vars.dist += vars.step;
	}
}
