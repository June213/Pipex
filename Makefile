NAME	= pipex

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror 

RM		= rm -rf

SRCS	= pipex.c \
		pipex_utils.c

OBJS    = $(SRCS:.c=.o)

LIBFT	= libft
LIBFT_A = $(LIBFT)/libft.a
LIBFT_INC = -I$(LIBFT)
LIBFT_OBJS = $(LIBFT)/*.o

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re
