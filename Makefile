CC = cc
CFLAGS = -Wall -Wextra -Werror -g -D BUFFER_SIZE=100
SRCS = get_next_line.c get_next_line_utils.c main.c
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
HEADER = get_next_line.h
BONUS_HEADER = get_next_line_bonus.h
NAME = get_next_line.out
BONUS_NAME = get_next_line_bonus.out

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

%.o: %.c $(HEADER) $(BONUS_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
