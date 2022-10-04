NAME		=	minishell.a

SRC =			src/error.c\
				./src/signals.c\
				./src/parser/parser.c\
				./src/parser/t_token.c\
				./src/parser/t_command.c\
				./src/parser/t_file.c\
				./src/parser/lexer_process.c\
				./src/parser/utils.c\
				./src/parser/expand_vars.c\
				./src/parser/expand_vars_string.c\
				./src/parser/split_tokens.c\
				./src/parser/parse_tokens.c\
				./src/parser/combine_tokens.c\
				./src/parser/debug.c\
				./src/executor/executor.c\
				./src/executor/builtins/cd.c\
				./src/executor/builtins/echo.c\
				./src/executor/builtins/env.c\
				./src/executor/builtins/exit.c\
				./src/executor/builtins/export.c\
				./src/executor/builtins/export_print.c\
				./src/executor/builtins/pwd.c\
				./src/executor/builtins/unset.c\
				./src/executor/builtins/builtin_utils.c\
				./src/executor/single_cmd.c\
				./src/executor/multiple_cmd.c\
				./src/executor/exec_multiple_cmd.c\
				./src/executor/open_files.c\
				./src/executor/heredoc.c\
				./src/executor/heredoc_utils.c\
				./src/executor/find_executable.c\
				./src/executor/wait_childs.c\
				./src/environment/ft_getenv.c\
				./src/environment/ft_environ.c\
				./src/environment/ft_unsetenv.c\
				./src/environment/ft_setenv.c

HEADERS		=	./include/environment.h \
				./include/executor.h \
				./include/minishell.h\
				./include/parser.h

LIBFT_LOC	=	lib/libft
LIB			=	lib/libft/libft.a

CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
OBJECTS		=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
		@$(MAKE) -s -C $(LIBFT_LOC)
		$(CC) $(CFLAGS) $(OBJECTS)  $(LIB) -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
		$(RM) $(OBJECTS)
		$(MAKE) -s -C $(LIBFT_LOC) clean

fclean: clean
		$(RM) $(NAME)
		$(MAKE) -s -C $(LIBFT_LOC) fclean

re: 	fclean all

.PHONY:	all clean fclean re