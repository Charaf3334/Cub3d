/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:34:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/04 11:12:11 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	render(t_data *data, t_mlx *mlx);

static int	close_window_x(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	return (0);
}

char get_map_tile(t_data *data, int x, int y)
{
    t_map *row = data->map_ll;
    for (int i = 0; i < y && row; i++)
        row = row->next;
    printf("x: %d | y: %d | strlen: %zu\n", x, y, ft_strlen(row->line));
    if (!row || x < 0 || x >= (int)ft_strlen(row->line))
        return '1'; // Treat out-of-bounds as wall
    
    return row->line[x];
}

void move_player(t_mlx *mlx, float dx, float dy)
{
    t_data *data = mlx->data;
    float new_x = data->player_x + dx;
    float new_y = data->player_y + dy;
    
    // Check collision in X direction
    if (get_map_tile(data, (int)(new_x), (int)data->player_y) != '1')
        data->player_x = new_x;
    
    // Check collision in Y direction
    if (get_map_tile(data, (int)data->player_x, (int)(new_y)) != '1')
        data->player_y = new_y;
}

void rotate_player(t_mlx *mlx, float angle)
{
    t_data *data = mlx->data;
    float old_dir_x = data->dir_x;
    float old_plane_x = data->plane_x;

    // Rotate direction vector
    data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
    data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
    
    // Rotate camera plane
    data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
    data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
    
    // Update player direction angle
    data->player_dir += angle;
    
    // Normalize angle between 0 and 2π
    if (data->player_dir < 0)
        data->player_dir += 2 * M_PI;
    if (data->player_dir > 2 * M_PI)
        data->player_dir -= 2 * M_PI;
}

// window.c

// Add this constant at the top of the file
#define MOVE_SPEED 0.1

// Update the key handling in close_window_esc
static int close_window_esc(int keycode, t_mlx *mlx)
{
    t_data *data = mlx->data;
    
    printf("%d\n", keycode);
    if (keycode == 53) // ESC
    {
        mlx_destroy_image(mlx->mlx, mlx->img);
        mlx_destroy_window(mlx->mlx, mlx->win);
        cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
    }
    else if (keycode == 13) // W - Move forward in facing direction
        move_player(mlx, data->dir_x * MOVE_SPEED, data->dir_y * MOVE_SPEED);
    else if (keycode == 1)  // S - Move backward
        move_player(mlx, -data->dir_x * MOVE_SPEED, -data->dir_y * MOVE_SPEED);
    else if (keycode == 2)  // A - Strafe left
        move_player(mlx, -data->dir_y * MOVE_SPEED, data->dir_x * MOVE_SPEED);
    else if (keycode == 0)  // D - Strafe right
        move_player(mlx, data->dir_y * MOVE_SPEED, -data->dir_x * MOVE_SPEED);
    else if (keycode == 124) // right arrow
        rotate_player(mlx, 0.1); // Rotate right
    else if (keycode == 123) // left arrow
        rotate_player(mlx, -0.1); // Rotate left
    
    render(mlx->data, mlx);
    return 0;
}

static void	close_handle(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1, close_window_esc, mlx);
	mlx_hook(mlx->win, 17, 0, close_window_x, mlx);
}


void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_tile(t_mlx *mlx, int x, int y, int color)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			my_mlx_pixel_put(mlx, x + i, y + j, color);
		}
	}
}

void render(t_data *data, t_mlx *mlx)
{
    t_map *map = data->map_ll;
    int y = 0;

    // Clear screen
    mlx_clear_window(mlx->mlx, mlx->win);
    ft_memset(mlx->addr, 0, HEIGHT * mlx->line_length);

	// Draw rays for 3D view
	for (int x = 0; x < WIDTH; x++) {
		t_ray	ray;
		t_dda	dda;
		
		init_ray(data, &ray, x);
		perform_dda(data, &ray);
		calculate_line(&ray, &dda);
		
		// Choose color based on wall direction
		int color;
		if (ray.side == 1) color = 0x8888FF; // Blue for north/south walls
		else color = 0xFF8888; // Red for east/west walls
		
		draw_ray(data, x, &dda, color);
	}
    
    // Draw map tiles
    while (map)
    {
        int x = 0;
        int i = 0;
        while (map->line[i])
        {
            int color;
            if (map->line[i] == '0')
                color = 0xD2B48C; // Floor - Tan/Sand, soft and natural
            else if (map->line[i] == '1')
                color = 0x2F4F4F;
            else
                color = 0x000000; // Other
            
            draw_tile(mlx, x * 20, y * 20, color);
            x++;
            i++;
        }
        y++;
        map = map->next;
    }

    // Draw player at actual position (smooth)
    int player_x = (int)(data->player_x * 20);
    int player_y = (int)(data->player_y * 20);
    
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            my_mlx_pixel_put(mlx, player_x + i, player_y + j, 0x0000FF);
        }
    }

    // Draw direction line
    int dir_x = player_x + (int)(data->dir_x * 10);
    int dir_y = player_y + (int)(data->dir_y * 10);
    
    // Simple line drawing
    float dx = dir_x - player_x;
    float dy = dir_y - player_y;
    float steps = fmax(fabs(dx), fabs(dy));
    
    for (int i = 0; i <= 30; i++) {
        float x = player_x + dx * (i / steps);
        float y = player_y + dy * (i / steps);
        my_mlx_pixel_put(mlx, (int)x, (int)y, 0xFF0000);
    }

    // Draw some rays on minimap for visualization
	for (int x = 0; x < WIDTH; x += 20) {
		t_ray	ray;
		init_ray(data, &ray, x);
		perform_dda(data, &ray);
		draw_ray_on_minimap(mlx, data, &ray);
	}
    
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}


int	window(t_data *data, t_free **free_nodes)
{
	t_mlx	*mlx;

	mlx = NULL;
	// data->free_nodes = free_nodes;
	data->mlx = ft_malloc(sizeof(t_mlx), free_nodes);
	mlx = data->mlx;
	mlx->data = data;
	mlx->mlx = mlx_init(); // mlx_destroy_display
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, TITLE);
	if (!mlx->win)
		return (1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (mlx_destroy_window(mlx->mlx, mlx->win), 1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		return (mlx_destroy_image(mlx->mlx, mlx->img), mlx_destroy_window(mlx->mlx, mlx->win), 1);
	render(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	close_handle(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
