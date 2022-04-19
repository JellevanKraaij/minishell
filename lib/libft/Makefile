# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jvan-kra <jvan-kra@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/19 15:45:22 by jvan-kra      #+#    #+#                  #
#    Updated: 2021/12/01 19:59:39 by jvan-kra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c 		\
ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c		\
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strnlen.c ft_islower.c\
ft_isupper.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c	\
ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c		\
ft_calloc.c ft_strdup.c ft_strcpy.c ft_substr.c ft_strjoin.c	\
ft_strtrim.c ft_split.c ft_findchr.c ft_nrlen.c ft_itoa.c 		\
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c		\
ft_putendl_fd.c ft_pow.c ft_putnbr_fd.c ft_strndup.c ft_lstnew.c\
ft_lstadd_front.c ft_lstsize.c ft_lstlast.c	ft_lstadd_back.c	\
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c			\
ft_reallocf.c ft_abs.c

SRCS := $(addprefix src/, $(SRCS))

HEADER_DIR = ./include
HEADER = $(HEADER_DIR)/libft.h

OBJS = ${SRCS:.c=.o}

CC = gcc

all: ${NAME}

%.o:%.c
	${CC} ${CFLAGS} -I$(HEADER_DIR) -c $< -o $@

${NAME}: ${OBJS} ${HEADER}
	${AR} rcs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus