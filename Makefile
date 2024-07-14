NAME 			= minishell
HDRDIR			= incl/

EXECDIR			= exec/
EXECSRCS		= ${EXECDIR}executor.c

PARSEDIR		= ${SRCSDIR}parse/
PARSESRCS		= ${PARSEDIR}ft_input_parse.c \
				#   ${PARSEDIR}ft_init_env.c

UTILDIR			= ${SRCSDIR}utils/
UTILSRCS		= ${UTILDIR}ft_utils.c ft_env_utils.c

SRCSDIR			= srcs/
SRCS			= ${SRCSDIR}main.c \
				  ${PARSEDIR}ft_input_parse.c \
				  ${PARSEDIR}ft_init_env.c \
				  ${UTILDIR}ft_utils.c \
				  ${UTILDIR}ft_env_utils.c

VPATH			= ${SRCSDIR} ${SRCSDIR}parse/ ${SRCSDIR}utils/
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