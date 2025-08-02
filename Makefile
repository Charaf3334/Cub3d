# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 10:33:55 by ctoujana          #+#    #+#              #
#    Updated: 2025/08/02 11:14:45 by zguellou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = #-Wextra -Wall -Werror #-g3 -fsanitize=address 
LINK = -lmlx -framework OpenGL -framework AppKit -lm
MLX = MLX/libmlx.a

SRCS =  mandatory/cub3D.c mandatory/free_nodes.c \
		mandatory/parsing/init_data.c mandatory/parsing/window.c mandatory/parsing/window_utils1.c mandatory/parsing/init_data_utils.c mandatory/parsing/init_data_utils2.c  mandatory/parsing/map_horiz_lines.c  mandatory/parsing/map_vert_lines.c\
		mandatory/parsing/parse_color.c mandatory/parsing/valid_map.c mandatory/parsing/map_ll.c \
		mandatory/parsing/init_player_dir.c \
		utils/libft/ft_strcmp.c utils/libft/ft_itoa.c utils/libft/ft_memcpy.c utils/libft/ft_strjoin3.c utils/libft/ft_strchr.c utils/libft/ft_memset.c utils/libft/ft_strtrim.c \
		utils/libft/ft_strlen.c utils/libft/ft_strdup.c utils/libft/ft_substr.c utils/libft/ft_split_libft.c \
		utils/libft/ft_atoi.c utils/libft/ft_lstlast.c \
		utils/get_next_line.c utils/utils1.c utils/utils2.c \
		mandatory/rays/rays.c mandatory/rays/render.c mandatory/rays/player_movement.c \
		mandatory/rays/map_utils.c \
		mandatory/rays/rays2.c
OBJS = $(SRCS:.c=.o)

B_SRCS = bonus/cub3D_bonus.c
B_OBJS= $(B_SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) 
	cc $(CFLAGS) -o $(NAME) $(OBJS)  $(LINK)
#if header modified should everything recompile

mandatory/%.o: mandatory/%.c ./mandatory/cub3D.h
	cc -c $(CFLAGS) $< -o $@

bonus:  $(B_OBJS) 
	cc $(CFLAGS) -o $(NAME) $(B_OBJS) $(LINK)

bonus/%.o: bonus/%.c ./bonus/cub3D_bonus.h
	cc -c $(CFLAG)  $< -o $@

clean:
	rm -rf $(OBJS) $(B_OBJS)

fclean: clean
	@rm -rf $(NAME)

re : fclean all
