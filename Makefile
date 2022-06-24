
RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

THFLAGS = -g -pthread

SRC = main.c libft_utils.c init.c times.c actions.c utils.c

OBJ = $(SRC:.c=.o)

NAME = philo

CHECKER_NAME = checker

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(THFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean: 
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
