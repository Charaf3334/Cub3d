/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:59:00 by zguellou          #+#    #+#             */
/*   Updated: 2025/08/02 14:52:07 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	get_map_tile(t_data *data, int x, int y)
{
	int		i;
	t_map	*row;

	row = data->map_ll;
	i = 0;
	while (i < y && row)
	{
		row = row->next;
		i++;
	}
	if (!row || x < 0 || x >= (int)ft_strlen(row->line))
		return ('1');
	return (row->line[x]);
}
