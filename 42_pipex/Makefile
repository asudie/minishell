NAME 			= pipex
HDRDIR			= incl/
SRCSDIR			= srcs/
SRCS			= ${SRCSDIR}main.c \
				  ${SRCSDIR}ft_utils.c
OBJS			= $(SRCS:.c=.o)
CFLAGS 			= -Wall -Wextra -Werror -I$(HDRDIR) -g

CC 				= cc
PRINTFDIR		= ft_printf/
PRINTF			= ${PRINTFDIR}libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) 
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(PRINTF)

$(PRINTF):
	make -C $(PRINTFDIR)

clean:
	rm -f $(OBJS)
	make fclean -C $(PRINTFDIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re