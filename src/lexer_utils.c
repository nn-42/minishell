#include "minishell.h"

t_token *create_token(t_token_type type, char *value)
{
        t_token *token;

        token = malloc(sizeof(t_token));
        if (!token)
                return (NULL);
        token->type = type;
        token->value = value;
        token->next = NULL;
        return (token);
}

void    add_token(t_token **tokens, t_token *new)
{
        t_token *current;

        if (!*tokens)
        {
                *tokens = new;
                return ;
        }
        current = *tokens;
        while (current->next)
                current = current->next;
        current->next = new;
}
