/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/30 23:41:24 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/03/30 23:41:24 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_PROMPT "minishell$> "

typedef enum e_token_labels
{
    WORD, //undefined
    SQUOTED, // string single quotes
    DQUOTED, // string double quotes
    RED_INPUT, // <
    RED_OUTPUT, // >
    RED_OUT_APPEND, //  >>
    RED_IN, //  <<
    PIPE, // |
    END
}   t_token_labels;

typedef struct s_tokenized
{
    int     token;
    char    *element;
}   t_tokenized;

//Errors
void	    perror_exit(const char *s, int error_code) __attribute__((noreturn));
void	    *null_exit(void	*ptr);
void	    print_error(char *name, char *error_desc, char *error);
void	    parse_exec(char *line);
void	    init_signals(void);
t_tokenized lexer_exec(char *line);

#endif
