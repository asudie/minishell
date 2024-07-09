NAME 			= minishell
HDRDIR			= incl/

EXECDIR			= exec/
EXECSRCS		= ${EXECDIR}executor.c

PARSEDIR		= parse/
PARSESRCS		= ${PARSEDIR}ft_parser.c

UTILDIR			= utils/
UTILSRCS		= ${UTILDIR}ft_utils.c

SRCSDIR			= srcs/
SRCS			= ${SRCSDIR}main.c \
				  ${SRCSDIR}${PARSESRCS} \
				  ${SRCSDIR}${UTILSRCS}
#				  ${SRCSDIR}${EXECSRCS}
OBJS			= $(SRCS:.c=.o)
CFLAGS 			= -Wall -Wextra -Werror -I$(HDRDIR) -g

LIBFTDIR		= libft/
LIBFT			= ${LIBFTDIR}libft.a

ALLOCDIR		= ft_destructor/
ALLOC			= $(ALLOCDIR)ft_alloc.a

CC 				= cc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(ALLOC)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(ALLOC) -o $(NAME) -lreadline

$(LIBFT):
	make -C $(LIBFTDIR)
	make bonus -C $(LIBFTDIR)

$(ALLOC):
	make -C $(ALLOCDIR)

clean:
	rm -f $(OBJS)
	make fclean -C $(LIBFTDIR)
	make fclean -C $(ALLOCDIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re