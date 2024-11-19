CC = cc
CFLAGS = -Wall -Wextra -Werror -g -D BUFFER_SIZE=100
SRCS = get_next_line.c get_next_line_utils.c main.c
OBJS = $(SRCS:.c=.o)
HEADER = get_next_line.h
NAME = get_next_line.out

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
