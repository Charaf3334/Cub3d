/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:47:14 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/26 14:43:53 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	len_strs(char **strs)
{
	int	i;
	
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	skip_zeroes(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	return (i);
}

int check_len_comma(t_data *data, char *str, t_free **free_nodes, char c)
{
	int	i;
	int	len_comma;

	i = 0;
	len_comma = 0;
	if (ft_strlen(str) < 5)
		return (print_error("len below 5"), 1);
	while (str[i])
	{
		if (str[i] == ',')
			len_comma++;
		i++;
	}
	if (len_comma != 2)
		return (print_error("Invalid color format: need exactly two commas"), 1);
	char **strs =  ft_split_libft(str, ",", free_nodes);
	if (len_strs(strs) < 3 || len_strs(strs) > 4 )
		return (print_error("Invalid color: need exactly three components"), 1);
	i = 0;
	while (strs[i])
	{
		if (strs[i][0] == '\0')
    		return (print_error("Empty color component not allowed"), 1);
		if (check_num(strs[i]))
			return (print_error("Color component must be digits only"), 1);
		int j = skip_zeroes(strs[i]);
		if (ft_strlen(&strs[i][j]) > 3)
			return (print_error("Color component cannot exceed 255"), 1);
		int	num = ft_atoi(strs[i]);
		if (num > 255)
			return (print_error("Color component cannot exceed 255"), 1);
		if (c == 'F')
		{
			if (i == 0)
				data->floor |= num << 16;
			else if (i == 1)
				data->floor |= num << 8;
			else if (i == 2)
				data->floor |= num;
		}
		else if (c == 'C')
		{
			if (i == 0)
				data->ceilling |= num << 16;
			else if (i == 1)
				data->ceilling |= num << 8;
			else if (i == 2)
				data->ceilling |= num;
		}
		i++;
	}
	return (0);
}

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
			return (print_error("Invalid texture path format"), 1);
		str[st + en] = '\0';
		if (!ft_strcmp("F", &str[st]))
		{
			if (check_len_comma(data, strs[1], free_nodes, 'F'))
				return (1);
		}
		else if (!ft_strcmp("C", &str[st]))
		{
			if (check_len_comma(data, strs[1], free_nodes, 'C'))
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

int	check_map_chars(char *line, int *flag)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	while (line[i])
	{
		if (is_sep(line[i], "NSWE"))
			(*flag)++;
		if (!is_sep(line[i], " 01NSWE\n"))
			return (1);
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
    int	start;
    int	end;
    
	start = 0;
    end = ft_strlen(line) - 1;
    while (line[start] && is_sep(line[start], " \t\n\v\f\r"))
        start++;
    if (line[start] == '\0')
        return (1);
    while (end >= 0 && is_sep(line[end], " \t\n\v\f\r"))
        end--;
    while (start <= end)
	{
        if (line[start] != '1' && line[start] != ' ')
            return (1);
		start++;
    }
    return (0);
}

int	check_in_between(t_map *head)
{
	int		i;
	int		j;
	int		end;
	int		start;
	t_map	*curr;
	
	curr = head;
	start = 0;
	end = ft_strlen(curr->line) - 1;
	while (curr->line[start] && is_sep(curr->line[start], " \t\n\v\f\r"))
		start++;
	if (curr->line[start] == '\0')
		return (1);
	while (end >= 0 && is_sep(curr->line[end], " \t\n\v\f\r"))
		end--;
	if (end < 0)
		return (1);
	if (curr->line[start] != '1' || curr->line[end] != '1')
		return (1);
	i = start;
	while (i <= end)
	{
		if (curr->line[i] == ' ')
		{
			j = i;
			while (j <= end && curr->line[j] == ' ')
				j++;
			if (j > end)
				return (1);
			if (curr->line[i - 1] != '1' || curr->line[j] != '1')
				return (1);
			i = j;
		}
		else
			i++;
	}
	return (0);
}

int	check_map_horiz_closed(t_map *head)
{
	int		i;
	t_map	*curr;

	i = 0;
	curr = head;
	if (!curr)
		return (print_error("Empty map"), 1);
	//horinzontal done
    while (curr)
    {
        if (i == 0 || !curr->next)  // First or last line
        {
            if (check_closed_first_last(curr->line))
            {
                printf("line1: |%s|\n", curr->line);
                print_error("Map not closed");
                return (1);
            }
        }
        else  // Middle lines
        {
            if (check_in_between(curr))
            {
                printf("line[%d]: |%s|\n", i, curr->line);
                printf("prev->line[%d]: |%s|\n", i, curr->prev->line);
                print_error("Map not closed");
                return (1);
            }
        }
        curr = curr->next;
        i++;
    }
    return (0);
}

int	handle_previous_lines(t_map *curr, int i)
{
	t_map *prev;

	prev = curr->prev;
	if (!prev || !prev->line || !prev->line[i])
		return (1);
	while (prev)
	{
		if (prev->line[i] == '1')
			return (0);
		else if (prev->line[i] == ' ')
			return (1);
		prev = prev->prev;
	}
	return (1);
}

int	handle_next_lines(t_map *curr, int i)
{
	t_map *next;

	next = curr->next;
	if (!next || !next->line || !next->line[i])
		return (1);
	while (next)
	{
		if (next->line[i] == '1')
			return (0);
		else if (next->line[i] == ' ')
			return (1);
		next = next->next;
	}
	return (1);
}

int	check_map_vertic_closed(t_map *head)
{
	int		i;
	t_map	*curr;

	i = 0;
	curr = head;
	// for (t_map *tmp = head; tmp; tmp = tmp->next)
	// 	printf("line: |%s|\n", tmp->line);
	//vertical
	while (curr)
	{
		i = 0;
		while (curr->line[i])
		{
			while (curr->line[i] && !is_sep(curr->line[i], "0WSEN"))
				i++;
			if (!curr->line[i])
				break ;
			if (handle_previous_lines(curr, i))
				return (printf("vertic line[%d]: |%s|\n", i, curr->line), print_error("Unclosed map fo9"), 1);
			if (handle_next_lines(curr, i))
				return (printf("vertic line[%d]: |%s|\n", i, curr->line), print_error("Unclosed map lte7t"), 1);
			i++;
		}
		curr = curr->next;
		i++;
	}
	return (0);
}

int	check_map_valid(t_data *data)
{
	t_map	*head;
	int		flag;
	int		i;
	
	i = 0;
	head = data->map_ll;
	while (head)
	{
		i = 0;
		while (is_sep(head->line[i], " \t\n\v\f\r01NSWE"))
			i++;
		if (!head->next)
			break;
		else if (!head->line[i])
			head = head->next;
		else
			return (printf("line[%d]: |%s|\n", i, head->line), print_error("Invalid map"), 1);
	}
	if (!head)
		return (print_error("Invalid map"), 1);
	head = data->map_ll;
	flag = 0;
	if (check_map_horiz_closed(data->map_ll))
		return (1);
	while (head)
	{
		if (check_map_chars(head->line, &flag))
			return (print_error("Invalid character in map"), 1);
		if (flag > 1)
			return (print_error("Too many players in map"), 1);
		head = head->next;
	}
	if (!flag)
		return (print_error("No player found in map"), 1);
	if (check_map_vertic_closed(data->map_ll))
		return (1);
	return (0);
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
