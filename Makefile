NAME 			= minishell
HDRDIR			= incl/
SRCSDIR			= srcs/
SRCS			= ${SRCSDIR}main.c \
				  ${SRCSDIR}ft_parser.c
OBJS			= $(SRCS:.c=.o)
CFLAGS 			= -Wall -Wextra -Werror -I$(HDRDIR) -g

LIBFTDIR		= libft/
LIBFT			= ${LIBFTDIR}libft.a

CC 				= cc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT) -lreadline

$(LIBFT):
	make -C $(LIBFTDIR)
	make bonus -C $(LIBFTDIR)

clean:
	rm -f $(OBJS)
	make fclean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re