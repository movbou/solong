NAME        = so_long
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
FT_PRINTF_DIR = ft_printf
FT_PRINTF  = ft_printf/libftprintf.a
LIBFT_LIB   = libft/libft.a
INCLUDES    = -Ilibft -Ift_printf
MLX_FLAGS   = -Lminilibx-linux -lmlx_Linux -lX11 -lXext
SRC         = so_long.c gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c \
			utils.c map_parsing.c mx_init.c player.c fill.c game.c valid_map.c errors.c \

all: $(LIBFT_LIB) $(FT_PRINTF) $(NAME)

$(NAME): $(LIBFT_LIB) $(FT_PRINTF) $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(MLX_FLAGS) $(LIBFT_LIB) $(FT_PRINTF) -o $(NAME)

$(LIBFT_LIB):
	@make -C libft

$(FT_PRINTF):
	@make -C ft_printf

clean:
	@make clean -C libft
	@make clean -C ft_printf

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@make fclean -C ft_printf

re: fclean all

.PHONY: fclean