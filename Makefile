SRCS	= ft_printf.c printf_states.c stdout_utils.c printf_args.c printf_mods.c

OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

LIBFT 	= libft

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			make -C $(LIBFT)
			cp libft/libft.a ./$(NAME)
			ar rcs ${NAME} ${OBJS}

bonus:		${NAME}

clean:
			rm -f ${OBJS} $(BONUS_OBJS)
			make clean -C $(LIBFT)

fclean:		clean
			rm -f ${NAME}
			make fclean -C $(LIBFT)

re:			fclean all

.PHONY:		all bonus clean fclean re
