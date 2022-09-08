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
SRCS = src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c \
src/ft_isprint.c src/ft_strlen.c src/ft_memset.c src/ft_bzero.c src/ft_memcpy.c \
src/ft_memmove.c src/ft_strlcpy.c src/ft_strlcat.c src/ft_strnlen.c src/ft_islower.c \
src/ft_isupper.c src/ft_toupper.c src/ft_tolower.c src/ft_strchr.c src/ft_strrchr.c \
src/ft_strncmp.c src/ft_memchr.c src/ft_memcmp.c src/ft_strnstr.c src/ft_atoi.c \
src/ft_calloc.c src/ft_strdup.c src/ft_strcpy.c src/ft_substr.c src/ft_strjoin.c \
src/ft_strtrim.c src/ft_split.c src/ft_findchr.c src/ft_nrlen.c src/ft_itoa.c \
src/ft_strmapi.c src/ft_striteri.c src/ft_putchar_fd.c src/ft_putstr_fd.c \
src/ft_putendl_fd.c src/ft_pow.c src/ft_putnbr_fd.c src/ft_strndup.c src/ft_lstnew.c \
src/ft_lstadd_front.c src/ft_lstsize.c src/ft_lstlast.c	src/ft_lstadd_back.c \
src/ft_lstdelone.c src/ft_lstclear.c src/ft_lstiter.c src/ft_lstmap.c \
src/ft_reallocf.c src/ft_abs.c src/ft_strntrim.c src/ft_strchrset.c src/ft_strjoin3.c \
src/ft_lsttoarray.c src/ft_dstrlen.c src/ft_dstrfree.c src/ft_strcmp.c src/ft_dstrdup.c \
src/ft_dstrtolst.c src/ft_realloc.c src/ft_splitset.c

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