/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:47:14 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/25 14:48:16 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int populate_data_1(char *line, t_free **free_nodes, t_data *data)
{
    line = ft_strtrim(line, " \t\v\f\r");
    int i = 0;
    while (line[i] && line[i] != ' ' && line[i] != '\n')
        i++;
    line[i] = '\0';
    if (!ft_strcmp("NO", line) || !ft_strcmp("WE", line) || 
        !ft_strcmp("EA", line) || !ft_strcmp("SO", line))
    {
        line[i] = ' ';
        char **strs = ft_split_libft(line, " \t\v\f\r", free_nodes);
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
	else if (!ft_strcmp("F", line) || !ft_strcmp("C", line))
		printf("F and C to be continued\n");
	else
		return (print_error("I think i smell a rat"), 1);
    return (0);
}

t_map	*create_new_node(char *line, t_free **free_nodes)
{
	t_map	*node;

	node = ft_malloc(sizeof(t_map), free_nodes);
	node->line = ft_strdup_normal(line, free_nodes);
	node->next = NULL;
	return (node);
}

int	map_ll_populate(char *line, t_free **free_nodes, t_data *data)
{
	t_map	*head;
	t_map	*current = ft_lstlast(data->map_ll);

	// if (check_map(line))
	// 	return (print_error("Invalid character in map"), 1);
	head = create_new_node(line, free_nodes);
	if (!current)
	{
		data->map_ll = head;
	}
	else
		current->next = head;
	return (0);
}

int	 populate_data(t_data *data, char *line, t_free **free_nodes, int *index)
{
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

int	check_map_chars(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	while (line[i])
	{
		if (!is_sep(line[i], " 01NSWE\n"))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// int	check_space_inline(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
		
// 		i++;
// 	}
// }

int check_closed_first_last(char *line)
{
    int i;
    int j;

	i = 0;
    while (line[i])
    {
        if (line[i] == '1')
            i++;
        else if (line[i] == ' ')
        {
            j = i;
            while (line[j] == ' ')
                j++;
            if (i == 0 || line[j] == '\0') 
                return (1);
            if (line[i - 1] != '1' || line[j] != '1')
                return (1);
            i = j;
        }
        else if (is_sep(line[i], " \t\n\v\f\r"))
            i++;
        else
            return (1);
	}
    return (0);
}

int	check_in_between(t_map *head)
{
	int		i;
	int		j;
	int		len;
	t_map	*cur;
	
	i = 0;
	cur = head;
	len = ft_strlen(cur->line) - 1;
	while (is_sep(cur->line[len], " \t\n\v\f\r"))
		len--;
	if (cur->line[0] != '1' || cur->line[len] != '1')
		return (1);
	while (cur->line[i])
	{
		if (cur->line[i] == ' ')
		{
			j = i;
			while (cur->line[j] == ' ')
				j++;
			if (i == 0 || cur->line[j] == '\0')
				return (1);
			if (cur->line[i - 1] != '1' || cur->line[j] != '1')
				return (1);
			i = j;
		}
		else
			i++;
	}
	return (0);
}

int	check_map_closed(t_map *head)
{
	int		i;
	t_map	*cur;

	i = 0;
	cur = head;
	while (cur)
	{
		if (i == 0 && check_closed_first_last(cur->line))
			return (1);
		else if (i > 0 && cur->next && check_in_between(cur))
			return (1);
		else if (i > 0 && !cur->next && (check_closed_first_last(cur->line)))
			return (1);
		cur = cur->next;
		i++;
	}
	return (0);
}

int	check_map_valid(t_data *data)
{
	t_map	*head;
	t_map	*tmp;
	int		i;
	
	i = 0;
	head = data->map_ll;
	while (head)
	{
		i = 0;
		while (is_sep(head->line[i], " \t\n\v\f\r"))
			i++;
		if (!head->line[i])
			head = head->next;
		else if (is_sep(head->line[i], "01NSWE"))
			break ;
		else
		{
			printf("line[%d]: %c\n", i, head->line[i]);
			return (print_error("invalid map"), 1);
		}
	}
	tmp = head;
	while (head)
	{
		if (check_map_chars(head->line))
			return (print_error("Invalid character in map"), 1);
		head = head->next;
	}
	if (check_map_closed(tmp))
		return (print_error("Map not closed"), 1);
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
		if (!line || !*line)
		{
			if (!line)
				print_error("Empty file");
			break ;
		}
		if (populate_data(data, line, free_nodes, &index))
			return (free(line), close(fd), 1);
		free(line);
	}
	if (check_map_valid(data))
		return (1);
	get_next_line(-42);
	close(fd);
	// print_nudes(data);
	if (!line)
		return (1);
	return (0);
}