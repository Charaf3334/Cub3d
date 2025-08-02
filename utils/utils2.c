/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:48:15 by ctoujana          #+#    #+#             */
/*   Updated: 2025/08/02 13:29:45 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
