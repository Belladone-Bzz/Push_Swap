SRC =	main.c

SRC +=	src/push_swap.c

SRC +=	modules/parsing/src/parsing.c	modules/parsing/src/compute_values.c \
		modules/parsing/src/get_flags.c

SRC +=	modules/operations/src/call_operations.c

SRC +=	modules/algorithms/common/algorithms_utils.c		\
		modules/algorithms/common/algorithms_array_utils.c	\
		modules/algorithms/src/simple_algo.c				\
		modules/algorithms/src/medium_algo.c				\
		modules/algorithms/src/complex_algo.c

OBJ =	$(SRC:.c=.o)

INC =	-I./include
CFLAGS =-g -Wall -Wextra -Werror
CC =	cc
NAME =	push_swap
LIBFT =	libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

$(LIBFT):
	cd libft && make all

clean:
	cd libft && make fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
