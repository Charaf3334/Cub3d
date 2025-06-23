/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:47:14 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/23 17:29:39 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int populate_data_1(char *str, t_free **free_nodes, t_data *data)
{
    char *tmp = str;
    str = ft_strtrim(str, " \t\v\f\r");
    free(tmp);
    int i = 0;
    while (str[i] && str[i] != ' ' && str[i] != '\n')
        i++;
    str[i] = '\0';
    if (!ft_strcmp("NO", str) || !ft_strcmp("WE", str) || 
        !ft_strcmp("EA", str) || !ft_strcmp("SO", str))
    {
        str[i] = ' ';
        char **strs = ft_split_libft(str, " \t\v\f\r", free_nodes);
        int len = 0;
        while (strs[len])
            len++;
        if (len != 2)
            return (print_error("Invalid texture path format"), 1);
        if (!ft_strcmp("NO", strs[0]))
            data->north = strs[1];
        else if (!ft_strcmp("WE", strs[0]))
            data->west = strs[1];
        else if (!ft_strcmp("EA", strs[0]))
            data->east = strs[1];
        else if (!ft_strcmp("SO", strs[0]))
            data->south = strs[1];
    }
	else if (!ft_strcmp("F", str) || !ft_strcmp("C", str))
		printf("F and C to be continued\n");
	else
		return (print_error("I think i smell a rat"), 1);
    return (0);
}

int	populate_data(t_data *data, char *str, t_free **free_nodes, int *index)
{
	(void)data;
	(void)index;
	if (str && str[0] == '\n')
		return (0);
	if (*index < 6)
	{
		*index += 1;
		if (populate_data_1(str, free_nodes, data))
			return (1);
	}
	return (0);
}

void	print_nudes(t_data *data)
{
	if (!data)
		return ;
	printf("EA: %s\n", data->east);
	printf("NO: %s\n", data->north);
	printf("SO: %s\n", data->south);
	printf("WE: %s\n", data->west);
}

int init_data(t_data *data, char *file, t_free **free_nodes)
{
	int		fd;
	char	*line;
	int		index;

	index = 0;
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		return (print_error("Invalid file") , 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || !*line)
		{
			if (!line)
				print_error("Empty file");
			break ;
		}
		if (populate_data(data, line, free_nodes, &index))
			return (close(fd), 1);
	}
	get_next_line(-42);
	close(fd);
	// print_nudes(data);
	if (!line)
		return (1);
	return (0);
}