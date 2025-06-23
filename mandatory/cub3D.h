/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:07:42 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/23 16:08:55 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_join
{
    size_t    i;
    size_t    j;
    size_t    s1_len;
    size_t    s2_len;
}    t_join;

typedef struct s_free
{
	void				*adr;
	struct s_free		*next;
}						t_free;

typedef struct s_data
{
    char *north;
    char *south;
    char *west;
    char *east;

    char *floor;
    char *ceilling;

    char **map;
}   t_data;

//libft
char	*ft_strchr(char *s, int c);
int     ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split_libft(char *str, char *c, t_free **free_nodes);
char	*ft_strtrim(char *s1, char *set);

//mandatory
int init_data(t_data *data, char *file, t_free **free_nodes);
void	cleanup_exit(t_data *data, int status);
void	free_strs(char **strs);
void	print_error(char *str);
void	ft_putstr_fd(char *str, int fd, int option);

//free_nodes
void	*ft_malloc(size_t size, t_free **free_nodes);

//utils
char	*get_next_line(int fd);

#endif