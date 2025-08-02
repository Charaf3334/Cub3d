# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 10:33:55 by ctoujana          #+#    #+#              #
#    Updated: 2025/08/02 14:04:07 by zguellou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = -Wextra -Wall -Werror #-g3 -fsanitize=address 
LINK = -lmlx -framework OpenGL -framework AppKit -lm

SRCS =  cub3D.c free_nodes.c \
		parsing/init_data.c parsing/window.c parsing/window_utils1.c parsing/init_data_utils.c parsing/init_data_utils2.c  parsing/map_horiz_lines.c  parsing/map_vert_lines.c\
		parsing/parse_color.c parsing/valid_map.c parsing/map_ll.c \
		parsing/init_player_dir.c \
		utils/libft/ft_strcmp.c utils/libft/ft_itoa.c utils/libft/ft_memcpy.c utils/libft/ft_strjoin3.c utils/libft/ft_strchr.c utils/libft/ft_memset.c utils/libft/ft_strtrim.c \
		utils/libft/ft_strlen.c utils/libft/ft_strdup.c utils/libft/ft_substr.c utils/libft/ft_split_libft.c \
		utils/libft/ft_atoi.c utils/libft/ft_lstlast.c \
		utils/get_next_line.c utils/utils1.c utils/utils2.c \
		rays/rays.c rays/render.c rays/player_movement.c \
		rays/map_utils.c \
		rays/rays2.c rays/render_helper.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS) 
	cc $(CFLAGS) -o $(NAME) $(OBJS) $(LINK)

%.o: %.c ./cub3D.h
	cc -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re : fclean all
