/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:47:14 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/26 17:28:09 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int populate_data_1(char *str, t_free **free_nodes, t_data *data)
{
	int st;
	int en;

	st = 0;
	en = 0;
	while (str[st] && is_sep(str[st], " \t\n\v\f\r"))
		st++;
	while (str[st + en] && !is_sep(str[st + en], " \t\n\v\f\r"))
		en++;
	str[st + en] = '\0';
	if ((!ft_strcmp("NO", &str[st]) && !data->north) || (!ft_strcmp("WE", &str[st]) && !data->west) || 
		(!ft_strcmp("EA", &str[st]) && !data->east) || (!ft_strcmp("SO", &str[st]) && !data->south))
	{
		str[st + en] = ' ';
		char **strs = ft_split_libft(str, " \t\n\v\f\r", free_nodes);
		int len = 0;
		while (strs[len])
			len++;
		if (len != 2)
			return (print_error("Invalid texture path format"), 1);
		if (strs[1] && !ft_strcmp("NO", strs[0]))
			data->north = strs[1];
		else if (strs[1] && !ft_strcmp("WE", strs[0]))
			data->west = strs[1];
		else if (strs[1] && !ft_strcmp("EA", strs[0]))
			data->east = strs[1];
		else if (strs[1] && !ft_strcmp("SO", strs[0]))
			data->south = strs[1];
	}
	else if (!ft_strcmp("F", &str[st]) || !ft_strcmp("C", &str[st]))
	{
		if ((!ft_strcmp(&str[st], "F") && data->floor) ||
            (!ft_strcmp(&str[st], "C") && data->ceilling))
            return (print_error("Duplicate color identifier"), 1);
		str[st + en] = ' ';
		char **strs = ft_split_libft(str, " \t\n\v\f\r", free_nodes);
		int len = 0;
		while (strs[len])
			len++;
		if (len != 2)
			return (print_error("Invalid color format"), 1);
		str[st + en] = '\0';
		if (!ft_strcmp("F", &str[st]))
		{
			if (parse_color(data, strs[1], free_nodes, 'F'))
				return (1);
		}
		else if (!ft_strcmp("C", &str[st]))
		{
			if (parse_color(data, strs[1], free_nodes, 'C'))
				return (1);
		}
	}
	else
		return (print_error("Unknown identifier"), 1);
	return (0);
}

t_map	*create_new_node(char *line, t_free **free_nodes)
{
	t_map	*node;

	node = ft_malloc(sizeof(t_map), free_nodes);
	int	i;
	i = 0;
	while (line && line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = '\0';
	node->line = ft_strdup_normal(line, free_nodes);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	map_ll_populate(char *line, t_free **free_nodes, t_data *data)
{
	t_map	*head;
	t_map	*current = ft_lstlast(data->map_ll);

	head = create_new_node(line, free_nodes);
	if (!current)
		data->map_ll = head;
	else
	{
		current->next = head;
		head->prev = current;
	}
	return (0);
}

int	 populate_data(t_data *data, char *line, t_free **free_nodes, int *index)
{
	int	flag;

	flag = 0;
	if (*index < 6)
	{
		if (line && line[0] == '\n')
			return (0);
		*index += 1;
		if (populate_data_1(line, free_nodes, data))
			return (1);
	}
	else
	{
		if (map_ll_populate(line, free_nodes, data))
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

int	check_line_valid(char *line)
{
	int	i;

	i = 0;
	while (is_sep(line[i], " \t\n\v\f\r"))
		i++;
	if (!line[i])
		return (0);
	return (1);
}

int	lltrim(t_map **map_ll)
{
	t_map	*tail;

	while (*map_ll)
	{
		if (check_line_valid((*map_ll)->line))
			break ;
		(*map_ll) = (*map_ll)->next;
	}
	if (!*map_ll)
		return (1);
	(*map_ll)->prev = NULL;
	tail = ft_lstlast((*map_ll));
	while (tail)
	{
		if (check_line_valid(tail->line))
			break ;
		tail = tail->prev;
	}
	tail->next = NULL;
	return (0);
}

int init_data(t_data *data, char *file, t_free **free_nodes)
{
	int		fd;
	char	*line;
	int		index;

	index = 0;
	data->map_ll = NULL;
	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		return (print_error("Invalid file") , 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || !*line) //(NULL or \0)
		{
			if (!line)
				print_error("Empty file");
			else if (!*line)
				free(line);
			break ;
		}
		if (populate_data(data, line, free_nodes, &index))
			return (free(line), close(fd), 1);
		free(line);
	}
	// for (t_map *tmp = data->map_ll; tmp; tmp = tmp->next)
	// 	printf("map_ll: |%s|\n", tmp->line);
	// exit(0);
	if (!data->map_ll)
		return (print_error("Empty map"), 1);
	if (lltrim(&data->map_ll))
		return (print_error("Empty map"), 1);
	if (check_map_valid(data))
		return (1);
	get_next_line(-42);
	close(fd);
	if (!line)
		return (1);
	// print_nudes(data);
	return (0);
}
