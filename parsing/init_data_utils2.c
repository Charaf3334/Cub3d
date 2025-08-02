/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:23:00 by ctoujana          #+#    #+#             */
/*   Updated: 2025/08/02 15:13:06 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	redir_fds_init(t_data *data, char *arr[])
{
	arr[0] = data->north;
	arr[1] = data->south;
	arr[2] = data->west;
	arr[3] = data->east;
	return (1);
}

int	assign_redir_fds(t_data *data)
{
	int		fd_tmp;
	char	*arr[4];
	int		i;

	i = -1;
	redir_fds_init(data, arr);
	while (++i < 4)
	{
		if (!arr[i])
			return (print_error("Empty File"), 1);
		fd_tmp = open(arr[i], O_RDONLY, 0644);
		if (fd_tmp == -1)
			return (perror(arr[i]), 1);
		close(fd_tmp);
	}
	return (0);
}
