NAME	= pipex

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror -fsanitize=address

RM		= rm -rf

SRCS	= pipex.c \
		pipex_utils.c \
		libft/libft.a \

$(NAME) :
	@make all -C libft
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

clean:
	@make clean -C libft

re: fclean all

.PHONY: all fclean clean re