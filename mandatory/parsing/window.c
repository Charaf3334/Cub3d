/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:34:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/07/02 13:22:16 by ctoujana         ###   ########.fr       */
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

void	move_player_forward(t_mlx *mlx)
{
	t_map *map = mlx->data->map_ll;
	while (map)
	{
		int		i = 0;
		while (map->line[i])
		{
			if (ft_strchr("NSWE", map->line[i]))
			{
				if (map->prev->line[i] == '0')
				{
					map->prev->line[i] = 'N';
					map->line[i] = '0';
				}
			}
			i++;
		}
		map = map->next;
	}
	printf("Move forward\n");
	// mlx->data->player->y--;
}

void	move_player_backward(t_mlx *mlx)
{
	t_map *map = mlx->data->map_ll;
	int		flag = 0;
	while (map)
	{
		int		i = 0;
		while (map->line[i])
		{
			if (!flag && map->next && ft_strchr("NSWE", map->line[i]))
			{
				flag = 1;
				if (map->next->line[i] == '0')
				{
					map->next->line[i] = 'N';
					map->line[i] = '0';
				}
			}
			i++;
		}
		map = map->next;
	}
	printf("Move backward\n");
	// mlx->data->player->y++;
}

void	strafe_player_left(t_mlx *mlx)
{
	t_map *map = mlx->data->map_ll;
	while (map)
	{
		int		i = 0;
		while (map->line[i])
		{
			if (ft_strchr("NSWE", map->line[i]))
			{
				if (map->line[i - 1] == '0')
				{
					map->line[i - 1] = 'N';
					map->line[i] = '0';
				}
			}
			i++;
		}
		map = map->next;
	}
	printf("Strafe left\n");
	// mlx->data->player->x--;
}

void	strafe_player_right(t_mlx *mlx)
{
	t_map *map = mlx->data->map_ll;
	int	flag = 0;
	while (map)
	{
		int		i = 0;
		while (map->line[i])
		{
			if (!flag && ft_strchr("NSWE", map->line[i]))
			{
				flag = 1;
				if (map->line[i + 1] == '0')
				{
					map->line[i + 1] = 'N';
					map->line[i] = '0';
				}
			}
			i++;
		}
		map = map->next;
	}
	printf("Strafe right\n");
	// mlx->data->player->x++;
}


static int	close_window_esc(int keycode, t_mlx *mlx)
{
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		cleanup_exit(mlx->data, mlx->data->free_nodes, 0);
	}
	else if (keycode == 13)
	{
		move_player_forward(mlx);
		render(mlx->data, mlx);
	}
	else if (keycode == 1)
	{
		move_player_backward(mlx);
		render(mlx->data, mlx);
	}
	else if (keycode == 0)
	{
		strafe_player_left(mlx);
		render(mlx->data, mlx);
	}
	else if (keycode == 2)
	{
		strafe_player_right(mlx);
		render(mlx->data, mlx);
	}
	return (0);
}

static void	close_handle(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1, close_window_esc, mlx);
	mlx_hook(mlx->win, 17, 0, close_window_x, mlx);
}


static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_tile(t_mlx *mlx, int x, int y, int color)
{
	for (int i = 1; i < 20; i++)
	{
		for (int j = 1; j < 20; j++)
		{
			my_mlx_pixel_put(mlx, x + i, y + j, color);
		}
	}
}

void	render(t_data *data, t_mlx *mlx)
{
	t_map	*map = data->map_ll;
	int		y = 0;

	// Clear image first (optional)
	mlx_clear_window(mlx->mlx, mlx->win);
	ft_memset(mlx->addr, 0, HEIGHT * mlx->line_length);

	while (map)
	{
		int		x = 0;
		int		i = 0;
		while (map->line[i])
		{
			int color;
			if (map->line[i] == '0')
				color = 0x00FF00;
			else if (map->line[i] == '1')
				color = 0xFF0000;
			else if (ft_strchr("NSWE", map->line[i]))
			{
				draw_tile(mlx, x * 20, y * 20, 0x00FF00);

				int px = x * 20 + (20 - 5) / 2;
				int py = y * 20 + (20 - 5) / 2;
				for (int dx = 0; dx < 5; dx++)
				{
					for (int dy = 0; dy < 5; dy++)
					{
						my_mlx_pixel_put(mlx, px + dx, py + dy, 0x0000FF);
					}
				}
				x++;
				i++;
				continue;
			}
			else
				color = 0x000000;
			
			draw_tile(mlx, x * 20, y * 20, color);
			x++;
			i++;
		}
		y++;
		map = map->next;
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
		return (mlx_destroy_image(mlx->mlx, mlx->img),
			mlx_destroy_window(mlx->mlx, mlx->win), 1);
	render(data, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	close_handle(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
