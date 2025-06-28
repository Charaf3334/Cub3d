/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:55:40 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/28 10:40:24 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	check_line_valid(char *line)
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

static t_map	*create_new_node(char *line, t_free **free_nodes)
{
	t_map	*node;
	int		i;

	node = ft_malloc(sizeof(t_map), free_nodes);
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
	t_map	*current;

	current = ft_lstlast(data->map_ll);
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
