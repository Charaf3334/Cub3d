/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:47:14 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/25 17:01:18 by zguellou         ###   ########.fr       */
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
		return (print_error("not enough commas"), 1);
	char **strs =  ft_split_libft(str, ",", free_nodes);
	if (len_strs(strs) < 3 || len_strs(strs) > 4 )
		return (print_error("Enter numbers"), 1);
	i = 0;
	while (strs[i])
	{
		if (strs[i][0] == '\0')
    		return (print_error("Empty number not allowed"), 1);
		if (check_num(strs[i]))
			return (print_error("Enter valid number"), 1);
		int j = skip_zeroes(strs[i]);
		if (ft_strlen(&strs[i][j]) > 3)
			return (print_error("Number bigger than 999"), 1);
		int	num = ft_atoi(strs[i]);
		if (num > 255)
			return (print_error("Number bigger than 255"), 1);
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
	printf("floor color: %d\n", data->floor);
	printf("ceilling color: %d\n", data->ceilling);
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
	else if ((!ft_strcmp("F", &str[st]) && !data->floor) || (!ft_strcmp("C", &str[st]) && !data->ceilling))
	{
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
		return (print_error("I think i smell a rat | SOOO | duplicate NO NO"), 1);
	return (0);
}

int	check_str(char *str, t_free **free_nodes)
{
	int	i;
	char **strs;

	i = 0;
	if (str && str[0] == '\n')
		return (1);
	strs = ft_split_libft(str, " \t\n\v\f\r", free_nodes);
	return (len_strs(strs) == 0);
}

int	populate_data(t_data *data, char *str, t_free **free_nodes, int *index)
{
	if (*index < 6)
	{
		if (check_str(str, free_nodes))
			return (0);
		*index += 1;
		return (populate_data_1(str, free_nodes, data));
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
	get_next_line(-42);
	close(fd);
	if (!line)
		return (1);
	print_nudes(data);
	return (0);
}
