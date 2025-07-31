/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:07:42 by zguellou          #+#    #+#             */
/*   Updated: 2025/07/31 16:02:15 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080
#define TITLE "Cub3D"
#define MOVE_SPEED 0.09
#define SCALE 20
#define W 13
#define S 1
#define A 2
#define D 0
#define LEFT_ARROW 123
#define RIGHT_ARROW 124

typedef struct s_dda
{
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_dda;

typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texture;

typedef struct s_render
{
	t_ray		ray;
	t_dda		dda;
	t_texture	*tex;
	float		wall_x;
	int			tex_x;
}	t_render;

typedef struct s_pop
{
	int		st;
	int		en;
	char	*str;
}	t_pop;

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
	char			*north;
	char			*south;
	char			*west;
	char			*east;
    int				floor;
    int				ceilling;
	t_free			**free_nodes;
	t_map			*map_ll;
	struct s_mlx	*mlx;

	float	player_x;
	float	player_y;

	float	player_dir;
    float	dir_x;        
    float	dir_y;        
    float	plane_x;      
    float	plane_y;      
	int		keys[256];
}   t_data;

typedef	struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_data	*data;
	t_texture   tex_north;
    t_texture   tex_south;
    t_texture   tex_west;
    t_texture   tex_east;
    t_texture   anim[21];
}	t_mlx;


typedef struct s_draw_ray
{
	float	ray_x;
	float	ray_y;
	float	step;
	float	dist;
	int		screen_x;
	int		screen_y;
}	t_draw_ray;

//render
typedef struct s_dir_line
{
	int		player_x;
	int		player_y;
	int		dir_x;
	int		dir_y;
	float	dx;
	float	dy;
	float	steps;
}	t_dir_line;


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
int		ft_atoi(const char *str);

t_map	*ft_lstlast(t_map *lst);
int		is_sep(char ch, char *c);

//mandatory_folder

//cub3d
int init_data(t_data *data, char *file, t_free **free_nodes);
void	free_strs(char **strs);
void	print_error(char *str);
void	ft_putstr_fd(char *str, int fd, int option);
int		check_ext(char *str, char *extension);

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

//init_player_direction
void	set_player_direction(t_data *data, char direction);

//map_ll
int		map_ll_populate(char *line, t_free **free_nodes, t_data *data);
int		lltrim(t_map **map_ll);

//valid_map
int		check_map_valid(t_data *data);

//map_vertic
int		check_map_vertic_closed(t_map *head);

//map_horiz
int		check_map_horiz_closed(t_map *head);

//utils_folder
char	*get_next_line(int fd);
//utils1
int		len_strs(char **strs);
int		is_num(char *str);
int		ft_strlen_char(char *str, char c);

//utils2
void	ft_putstr_fd(char *str, int fd, int option);
void	print_error(char *str);
void	free_strs(char **strs);
void	cleanup_exit(t_data *data, t_free **free_nodes, int status);

//init_data_utils
int		floor_and_ceilling_valid(t_pop *vars);
int		floor_and_ceilling(t_pop *vars, t_data *data, t_free **free_nodes);
int		is_texture_valid(t_pop *vars, t_data *data);
int		directions_populate(t_pop *vars, t_data *data, t_free **free_nodes);
int		assign_redir_fds(t_data *data);

//window
int		window(t_data *data, t_free **free_nodes);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
char	get_map_tile(t_data *data, int x, int y);
void	destroy_imgs(int index, t_mlx *mlx);

//rays/ rays.c 
void	draw_ray_on_minimap(t_mlx *mlx, t_data *data, t_ray *ray);
void	draw_ray(t_data *data, int x, t_dda *dda, t_render *vars);
void	calculate_line(t_ray *ray, t_dda *dda);
void	perform_dda(t_data *data, t_ray *ray);
void	init_ray(t_data *data, t_ray *ray, int x);

//render.c
void	render(t_data *data, t_mlx *mlx);

//player_movement
int	handle_keypress(int keycode, t_mlx *mlx);
int handle_keyrelease(int keycode, t_mlx *mlx);
void	move_player(t_mlx *mlx, float dx, float dy);
void rotate_player(t_mlx *mlx, float angle);

//map_utils
char	get_map_tile(t_data *data, int x, int y);
void	draw_block(t_mlx *mlx, int x, int y, int color);

//rays2.c
void	assign_delta_x_y(t_ray *ray);
void	init_ray_step_and_dist(t_ray *ray, t_data *data);
void	init_ray(t_data *data, t_ray *ray, int x);
void	perform_dda(t_data *data, t_ray *ray);

#endif