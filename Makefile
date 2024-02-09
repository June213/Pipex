NAME	= pipex

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror -fsanitize=address

RM		= rm -rf

SRCS	= pipex.c \
		libft/libft.a \

all: $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(NAME)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make all -C libft

re: fclean all

.PHONY: all fclean clean re