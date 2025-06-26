/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:07:42 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/26 17:57:41 by zguellou         ###   ########.fr       */
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

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
	struct s_map	*prev;
}   t_map;

typedef struct s_data
{
	char *north;
	char *south;
	char *west;
	char *east;

    int floor;
    int ceilling;

	t_map *map_ll;
}   t_data;

//libft
char	*ft_strchr(char *s, int c);
int     is_sep(char ch, char *c);
int     ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_strdup_normal(char *str, t_free **free_nodes);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split_libft(char *str, char *c, t_free **free_nodes);
char	*ft_strtrim(char *s1, char *set);
int ft_atoi(const char *str);

t_map	*ft_lstlast(t_map *lst);
int    is_sep(char ch, char *c);

//mandatory_folder

//cub3d
int init_data(t_data *data, char *file, t_free **free_nodes);
void	free_strs(char **strs);
void	print_error(char *str);
void	ft_putstr_fd(char *str, int fd, int option);

//free_nodes
void	*ft_malloc(size_t size, t_free **free_nodes);
void	ft_lstadd_front(t_free **lst, t_free *new);
void	ft_lstclear(t_free **lst);
void	cleanup_exit(t_data *data, t_free **free_nodes, int status);

//parse_color
int		parse_color(t_data *data, char *str, t_free **free_nodes, char c);
void	set_color(t_data *data, char c, int index, int num);
int		process_color(char *color, int *num_out);
int		skip_zeroes(char *str);

//map_ll
int	map_ll_populate(char *line, t_free **free_nodes, t_data *data);
int	lltrim(t_map **map_ll);

//valid_map
int check_map_valid(t_data *data);

//map_vertic
int		check_map_vertic_closed(t_map *head);

//map_horiz
int		check_map_horiz_closed(t_map *head);

//utils_folder
char	*get_next_line(int fd);
//utils1
int	len_strs(char **strs);
int	is_num(char *str);
int	ft_strlen_char(char *str, char c);

#endif