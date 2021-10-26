SRCFOLD		= srcs/

BONUSFOLD	= srcs_bonus/

SRCS_BONUS	=	${BONUSFOLD}pipex_bonus.c \
				${BONUSFOLD}ft_strchr.c \
				${BONUSFOLD}ft_strcmp.c \
				${BONUSFOLD}ft_strncmp.c \
				${BONUSFOLD}ft_strlen.c \
				${BONUSFOLD}ft_split.c \
				${BONUSFOLD}ft_putchar_fd.c \
				${BONUSFOLD}ft_putstr_fd.c \
				${BONUSFOLD}ft_putendl_fd.c \
				${BONUSFOLD}ft_strndup.c \
				${BONUSFOLD}ft_strdup.c \
				${BONUSFOLD}ft_memset.c \
				${BONUSFOLD}ft_memcpy.c \
				${BONUSFOLD}ft_free_tab.c \
				${BONUSFOLD}get_next_line.c \
				${BONUSFOLD}get_next_line_utils.c \
				${BONUSFOLD}ft_lstclear.c \
				${BONUSFOLD}ft_lstdelone.c \
				${BONUSFOLD}ft_lstnew.c \
				${BONUSFOLD}ft_lstlast.c \
				${BONUSFOLD}ft_lstadd_back.c \
				${BONUSFOLD}ft_strjoin.c

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
