/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:28:58 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/23 13:19:24 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/cub3D.h"

static char	*ft_strjoin_get(char *s1, char *s2)
{
	char	*str;
	t_join	var;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	var.s1_len = ft_strlen(s1);
	var.s2_len = ft_strlen(s2);
	str = (char *)malloc((var.s1_len + var.s2_len + 1));
	if (!str)
		return (NULL);
	var.i = 0;
	while (var.i < var.s1_len)
	{
		str[var.i] = s1[var.i];
		var.i++;
	}
	var.j = 0;
	while (var.j < var.s2_len)
		str[var.i++] = s2[var.j++];
	str[var.i] = '\0';
	return (str);
}

static char	*cleanup_joined(char *checkpoint, char *buffer)
{
	char	*temp;

	temp = checkpoint;
	checkpoint = ft_strjoin_get(checkpoint, buffer);
	free(temp);
	return (checkpoint);
}

static char	*read_file(int fd, char *checkpoint)
{
	char	*buffer;
	ssize_t	readed;

	buffer = NULL;
	while (!(ft_strchr(checkpoint, '\n')))
	{
		buffer = malloc((size_t)1 + 1);
		if (!buffer)
			return (free(checkpoint), checkpoint = NULL, NULL);
		readed = read(fd, buffer, 1);
		if (readed <= 0)
		{
			free(buffer);
			if (readed == -1)
				return (free(checkpoint), checkpoint = NULL, NULL);
			break ;
		}
		buffer[readed] = '\0';
		checkpoint = cleanup_joined(checkpoint, buffer);
		free(buffer);
		if (!checkpoint)
			return (NULL);
	}
	return (checkpoint);
}

static void	free_static(int fd, char *checkpoint)
{
	if (fd == -42)
	{
		free(checkpoint);
		checkpoint = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*checkpoint;
	char		*line;
	int			i;
	char		*tmp;

	i = 0;
	free_static(fd, checkpoint);
	if (fd < 0)
		return (NULL);
	if (!(ft_strchr(checkpoint, '\n')))
		checkpoint = read_file(fd, checkpoint);
	if (!checkpoint)
		return (NULL);
	while (checkpoint[i] && checkpoint[i] != '\n')
		i++;
	if (checkpoint[i] == '\n')
		i++;
	line = ft_substr(checkpoint, 0, i);
	if (!line)
		return (free(checkpoint), checkpoint = NULL, NULL);
	tmp = checkpoint;
	checkpoint = ft_substr(checkpoint, i, (ft_strlen(checkpoint) - i));
	free(tmp);
	return (line);
}
