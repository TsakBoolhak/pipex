SRCFOLD		= srcs/

BONUSFOLD	= srcs/

SRCS_BONUS	=	${SRCFOLD}pipex.c \
				${SRCFOLD}ft_split.c \
				${SRCFOLD}basic_tools.c \
				${SRCFOLD}basic_tools2.c \
				${SRCFOLD}pipex_tools.c \
				${SRCFOLD}pipex_tools2.c

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

IFLAGS		= -Iincludes

RM			= rm -f

%.o: %.c
	${CC} ${IFLAGS} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		 ${OBJS}
	${CC} ${IFLAGS} ${CFLAGS} ${OBJS} -o ${NAME}

${NAME_BONUS}:		 ${OBJS_BONUS}
	${CC} ${IFLAGS} ${CFLAGS} ${OBJS_BONUS} -o ${NAME_BONUS}

all:			${NAME}

bonus:			${NAME_BONUS}

clean:
	${RM} ${OBJS}

clean_bonus:
	${RM} ${OBJS_BONUS}

fclean:			clean
	${RM} ${NAME}

fclean_bonus:	clean_bonus
	${RM} ${NAME_BONUS}

re:				fclean all

re_bonus:		fclean_bonus bonus

.PHONY:			all clean fclean re bonus clean_bonus fclean_bonus re_bonus
