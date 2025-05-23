NAME = fdf
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror -I./includes

# Sources
SRC_DIR = src/
SRCS = $(SRC_DIR)core/main.c \
       $(SRC_DIR)core/init.c \
       $(SRC_DIR)core/cleanup.c \
       $(SRC_DIR)parsing/parser_map.c \
       $(SRC_DIR)parsing/checker.c \
       $(SRC_DIR)parsing/utils_parser.c \
       $(SRC_DIR)graphics/draw.c \
       $(SRC_DIR)graphics/pixel_put.c \
       $(SRC_DIR)graphics/transformations.c \
       $(SRC_DIR)events/handle_key.c \
       $(SRC_DIR)utils/get_next_line.c \
       $(SRC_DIR)utils/memory.c \
       $(SRC_DIR)utils/get_next_line_utils.c \
       $(SRC_DIR)utils/ft_split.c \
       $(SRC_DIR)utils/ft_atoi.c \
       $(SRC_DIR)utils/ft_strlcpy.c \
       $(SRC_DIR)utils/ft_strcmp.c \
       $(SRC_DIR)utils/ft_strrchr.c \
       $(SRC_DIR)utils/ft_isutils.c \
       $(SRC_DIR)utils/ft_abs.c \
       $(SRC_DIR)utils/ft_memset.c \

# Objects
OBJ_DIR = obj/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Libraries
MLX_DIR = libs/mlx/
MLX = $(MLX_DIR)libmlx.a

# Includes
INCLUDES = -I./includes -I$(MLX_DIR)

# Libraries flags
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: lib $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile ./includes/fdf.h $(MLX)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

lib:
	@make -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(MLX_DIR) clean

fclean: clean
	make -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib

