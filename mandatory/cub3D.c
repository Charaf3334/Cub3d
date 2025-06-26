/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:35:04 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/26 15:36:04 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_putstr_fd(char *str, int fd, int option)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, str, len);
	if (option == 1)
		write(fd, "\n", 1);
}

void	print_error(char *str)
{
	ft_putstr_fd("Error", 2, 1);
	ft_putstr_fd(str, 2, 1);
}

static int	check_arg1(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '.')
		{
			if (i == 0 || ft_strcmp(&str[i], ".cub"))
				return (1);
		}
	}
	if (!ft_strchr(str, '.'))
		return (1);
	return (0);
}

static int	check_args(int ac, char **av)
{
	if (ac != 2)
		return (print_error("Usage example: ./cub3D cubs/test.cub"), 1);
	else
	{
		if (check_arg1(av[1]))
			return (print_error("Enter a valid .cub file"), 1);
	}
	return (0);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	cleanup_exit(t_data *data, t_free **free_nodes, int status)
{
	(void)data;
	ft_lstclear(free_nodes);
	exit(status);
}

void f()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;
	t_free	*free_nodes;

	// atexit(f);
	free_nodes = NULL;
	if (check_args(ac, av))
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	if (init_data(&data, av[1], &free_nodes))
		cleanup_exit(&data, &free_nodes, 1);
	printf("Success\n");
	cleanup_exit(&data, &free_nodes, 0);
	return (0);
}
