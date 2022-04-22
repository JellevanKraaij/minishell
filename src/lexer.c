#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int    get_quoted(char *line, int i)
{
    char        token;
    t_tokenized tokenized;

    token = line[i];
    if(token == '\'')
        tokenized.token = SQUOTED;
    if(token == '\"')
        tokenized.token = DQUOTED;
    tokenized.element = ft_substr(line[i], line[i], ft_strchr(line[i], token) - ft_strchr(line[i + 1], token));
    return(i + (ft_strchr(line[i], token) - ft_strchr(line[i + 1], token)));    
}

int    get_sym(char *line, int i)
{
    t_tokenized tokenized;

    if (line[i] == '<')
    {
        tokenized.token = RED_INPUT;
        tokenized.element = "<";
        return(i + 1);
    }
    if (line[i] == '>')
    {
        tokenized.token = RED_OUTPUT;
        tokenized.element = ">";
        return(i + 1);
    }
    if (line[i] == '>>')
    {
        tokenized.token = RED_OUT_APPEND;
        tokenized.element = ">>";
        return(i + 2);
    }
    if (line[i] == '<<')
    {
        tokenized.token = RED_IN;
        tokenized.element = ">>";
        return(i + 2);
    }
    if (line[i] == '|')
    {
        tokenized.token = PIPE;
        tokenized.element = "|";
        return(i + 1);
    }
}

int     get_word(char *line, int i)
{
    t_tokenized tokenized;


}

void	lexer_exec(char *line)
{
    int i;

    i = 0;
    if (!line[i])
        return (-1);
    while(line[i])
    {
        while (line[i] == ' ')
            i++;
        if (line[i] == '\'' || line[i] == '\"')
            i = get_quoted(line, i);
        if (line[i] == '&' || line[i] == '<' || line[i] == '>' || line[i] == '|' || line[i] == '>>')
            i = get_sym(line, i);
            // Add find word: cuts a string when encounters a space or a special character as above.
            
    }
    
}