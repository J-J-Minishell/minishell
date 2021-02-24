# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/05 08:30:00 by jgalian-          #+#    #+#              #
#    Updated: 2019/12/10 11:56:40 by jgalian-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRCS		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
				ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
				ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
				ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
				ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
				ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
				ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_free_ptr.c \


OBJS        =   ${SRCS:.c=.o}

BONUS_SRCS	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJS	=	${BONUS_SRCS:.c=.o}

CC          =   gcc

CFLAGS      =   -Wall -Wextra -Werror

LFLAGS      =   -c -g

RM			=	rm -f

all:		$(NAME)

$(NAME):	${SRCS} libft.h
	${CC} ${CFLAGS} ${LFLAGS} ${SRCS}
	ar -rc ${NAME} ${OBJS}
	ranlib ${NAME}

bonus:
	${CC} ${CFLAGS} ${LFLAGS} ${BONUS_SRCS}
	ar -rc ${NAME} ${BONUS_OBJS}
	ranlib ${NAME}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

rebonus:	fclean bonus

.PHONY:		all clean fclean re
