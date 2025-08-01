/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:35:04 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/01 13:28:58 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_ext(char *str, char *extension)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '.')
		{
			if (i == 0 && !ft_strcmp(&str[i], extension))
				return (1);
			else if (i > 0 && !ft_strcmp(&str[i], extension))
				return (0);
		}
	}
	if (!ft_strchr(str, '.'))
		return (1);
	return (1);
}

static int	check_args(int ac, char **av)
{
	if (ac != 2)
		return (print_error("Usage example: ./cub3D cubs/test.cub"), 1);
	else
	{
		if (check_ext(av[1], ".cub"))
			return (print_error("Enter a valid .cub file"), 1);
	}
	if (WIDTH > 1920 || HEIGHT > 1080)
		return (print_error("Screen is way too big"), 1);
	return (0);
}

void f() {
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;
	t_free	*free_nodes;

	atexit(f);
	free_nodes = NULL;
	if (check_args(ac, av))
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	data.free_nodes = &free_nodes;
	if (init_data(&data, av[1], &free_nodes))
		cleanup_exit(&data, &free_nodes, 1);
	if (window(&data, &free_nodes))
		cleanup_exit(&data, &free_nodes, 1);
	cleanup_exit(&data, &free_nodes, 0);
}
