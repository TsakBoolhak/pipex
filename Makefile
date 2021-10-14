SRCFOLD		= srcs/

BONUSFOLD	= srcs_bonus/

SRCS_BONUS	=	${BONUSFOLD}pipex_bonus.c

SRCS		=	${SRCFOLD}pipex.c \
				${SRCFOLD}ft_split.c \
				${SRCFOLD}basic_tools.c \
				${SRCFOLD}basic_tools2.c \
				${SRCFOLD}pipex_tools.c \
				${SRCFOLD}pipex_tools2.c

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME		= pipex

NAME_BONUS	= pipex_bonus

CC			= clang

CFLAGS		= -Wall -Wextra -Werror

IFLAGS		= -Iincludes -Ilibft

RM			= rm -f

%.o: %.c
	${CC} ${IFLAGS} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		 ${OBJS}
	${CC} ${IFLAGS} ${CFLAGS} ${OBJS} -o ${NAME}

${NAME_BONUS}:		 ${OBJS_BONUS}
	make -C libft
	${CC} ${IFLAGS} ${CFLAGS} ${OBJS_BONUS} -o ${NAME_BONUS} -Llibft -lft

all:			${NAME}

bonus:			${NAME_BONUS}

clean:
	${RM} ${OBJS}

clean_bonus:
	${RM} ${OBJS_BONUS}
	make clean -C libft

fclean:			clean
	${RM} ${NAME}

fclean_bonus:	clean_bonus
	${RM} ${NAME_BONUS}
	make fclean -C libft

re:				fclean all

re_bonus:		fclean_bonus bonus

.PHONY:			all clean fclean re bonus clean_bonus fclean_bonus re_bonus
