NAME			= 	libftprintf.a

SRCS 			= 	ft_printf.c \
					get_next_line.c \
					get_next_line_utils.c

LIBFTDIR		=	libft

LIBFTOBJS		=	libft/libft.a

OBJS			= 	${SRCS:.c=.o}

CC 				= 	cc

CFLAGS 			= 	-Wall -Wextra -Werror

RM				= 	rm -rf

AR				=	ar -rc

all: ${LIBFTDIR} ${NAME}

${NAME}: ${OBJS}
	cp ${LIBFTOBJS} ./${NAME}
	${AR} ${NAME} ${OBJS}

${OBJS}:
	${CC} -c ${CFLAGS} ${SRCS}

${LIBFTDIR}:
	cd ${LIBFTDIR} && ${MAKE}

clean:
	${RM} ${OBJS}
	cd ${LIBFTDIR} && ${MAKE} clean

fclean:	clean
	${RM} ${NAME}
	cd ${LIBFTDIR} && ${MAKE} fclean

re: fclean all

.PHONY:	all clean fclean re ${LIBFTDIR}