
NAME = fdf 

SRCS = fdf.c \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS =
MAKEFLAGS+=--no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	$(cc) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@


clean:
	rm -f $(OBJS)
	@echo "Object files removed."

fclean: clean
	rm -f $(NAME)
	@echo "Library $(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
