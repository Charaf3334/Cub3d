/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:42:00 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 14:08:11 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculate_line(t_ray *ray, t_dda *dda)
{
	if (ray->wall_dist < 0.000001)
		ray->wall_dist = 0.000001;
	dda->line_height = (int)(HEIGHT / ray->wall_dist);
	dda->draw_start = HEIGHT / 2 - dda->line_height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = HEIGHT / 2 + dda->line_height / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT - 1;
}

void	draw_ray(t_data *data, int x, t_dda *dda, t_render *vars)
{
	t_draw_ray1	r;

	ft_memset(&r, 0, sizeof(t_draw_ray1));
	r.y = 0;
	while (r.y < dda->draw_start)
		my_mlx_pixel_put(data->mlx, x, r.y++, data->ceilling);
	r.step = (1.0 * vars->tex->height) / dda->line_height;
	r.tex_start_offset_on_wall = dda->draw_start - (HEIGHT / 2.0) \
		+ (dda->line_height / 2.0);
	r.tex_starting_pos = r.tex_start_offset_on_wall * r.step;
	while (r.y <= dda->draw_end)
	{
		r.tex_y = (int)r.tex_starting_pos;
		if (r.tex_y < 0)
			r.tex_y = 0;
		else if (r.tex_y >= vars->tex->height)
			r.tex_y = vars->tex->height - 1;
		r.color = *(int *)(vars->tex->addr + (r.tex_y * \
			vars->tex->line_len + vars->tex_x * (vars->tex->bpp / 8)));
		my_mlx_pixel_put(data->mlx, x, r.y, r.color);
		r.tex_starting_pos += r.step;
		r.y++;
	}
	while (r.y < HEIGHT)
		my_mlx_pixel_put(data->mlx, x, r.y++, data->floor);
}
