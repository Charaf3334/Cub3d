NAME = cub3D
CFLAGS = -Wextra -Wall -Werror -g3 -fsanitize=address
LINK = -lmlx -framework OpenGL -framework AppKit -lm
MLX = MLX/libmlx.a

SRCS = mandatory/cub3D.c  mandatory/init_data.c mandatory/free_nodes.c\
		utils/libft/ft_strcmp.c utils/libft/ft_strchr.c utils/libft/ft_memset.c utils/libft/ft_strtrim.c \
		utils/libft/ft_strlen.c utils/libft/ft_strdup.c utils/libft/ft_substr.c utils/libft/ft_split_libft.c \
		utils/get_next_line.c
OBJS = $(SRCS:.c=.o)

B_SRCS = bonus/cub3D_bonus.c
B_OBJS= $(B_SRCS:.c=.o)




all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(MLX) $(OBJS) $(LINK)

%.o: mandatory/%.c ./mandatory/cub3D.h
	cc -c $(CFLAGS) $< -o $@

bonus: $(MLX) $(B_OBJS)
	cc $(CFLAGS) -o $(NAME) $(MLX) $(B_OBJS) $(LINK)

%.o: bonus/%.c ./bonus/cub3D_bonus.h
	cc -c $(CFLAG)  $< -o $@

$(MLX):
	@make -C ./MLX

clean:
	@rm -rf $(OBJS) $(B_OBJS)

fclean: clean
	@make clean -C ./MLX
	@rm -rf $(NAME)

re : fclean all