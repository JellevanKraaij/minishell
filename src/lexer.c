#include "minishell.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// static int    get_quoted(char *line, int i)
// {
//     char        token;
//     t_tokenized tokenized;

//     token = line[i];
//     if(token == '\'')
//         tokenized.token = SQUOTED;
//     if(token == '\"')
//         tokenized.token = DQUOTED;
//     tokenized.element = ft_substr(&line[i], 0, ft_strchr(&line[i], token) - ft_strchr(&line[i + 1], token));
//     return(i + (ft_strchr(&line[i], token) - ft_strchr(&line[i + 1], token)));    
// }

// static int    get_sym(char *line, int i)
// {
//     t_tokenized tokenized;

//     if (line[i] == '>' && line[i + 1] == '>')
//     {
//         tokenized.token = RED_OUT_APPEND;
//         tokenized.element = ">>";
//         return(i + 2);
//     }
//     else if (line[i] == '<' && line[i + 1] == '<')
//     {
//         tokenized.token = RED_IN;
//         tokenized.element = ">>";
//         return(i + 2);
//     }
//     else if (line[i] == '<')
//     {
//         tokenized.token = RED_INPUT;
//         tokenized.element = "<";
//         return(i + 1);
//     }
//     else if (line[i] == '>')
//     {
//         tokenized.token = RED_OUTPUT;
//         tokenized.element = ">";
//         return(i + 1);
//     }
//     else if (line[i] == '|')
//     {
//         tokenized.token = PIPE;
//         tokenized.element = "|";
//         return(i + 1);
//     }
//     return(i);
// }

static int     get_word(char *line, int i, t_tokenized *tokenized)
{
    int start;

    start = i;
    tokenized->token = WORD;
    while(line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>' && line[i] != '|')
        i++;
    printf("This start: %i\n", start);
    // printf("This i: %i\n", i);
    tokenized->element = ft_substr(&line[start], 0, i - start);
    return(i);
}

t_tokenized	lexer_exec(char *line)
{
    t_tokenized tokenized;
    int         i;

    i = 0;
    // if (!line[i])
        // return (-1);
    while(line[i])
    {
        while (line[i] == ' ')
            i++;
        // if (line[i] == '\'' || line[i] == '\"')
            // i = get_quoted(line, i); //without care for non closing 
        // if (line[i] == '<' || line[i] == '>' || line[i] == '|')
            // i = get_sym(line, i);
        // else
            i += get_word(line, i, &tokenized);
            return(tokenized);
    i++;            
    }
    tokenized.token = END;
    return(tokenized);
}