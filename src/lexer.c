#include "minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_word_end(char c)
{
	return (c == ' ' || c == '\t' || c == '\0' || is_operator(c));
}

char	*extract_word(char *input, size_t *i)
{
	int		start;
	int		len;
	char	quote;

	start = *i;
	quote = 0;

	while (input[*i])
	{
		if (!quote && is_word_end(input[*i]))
			break ;
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!quote)
				quote = input[*i];
			else if (quote == input[*i])
				quote = 0;
		}
		(*i)++;
	}
	if (quote != 0)
		return (NULL);
	len = *i - start;
	return (ft_substr(input, start, len));
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

t_token *tokenize(char *input)
{
	t_token	*tokens;
	size_t	i;
	char	*word;
	
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			i++;
			continue ;
		}
		if (input[i] == '|')
		{
			add_token(&tokens, create_token(TOKEN_PIPE, ft_strdup("|")));
			i++;
			continue ;
		}
		if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&tokens, create_token(TOKEN_REDIR_APPEND, ft_strdup(">>")));
				i += 2;
			}
			else 
			{
				add_token(&tokens, create_token(TOKEN_REDIR_OUT, ft_strdup(">")));
				i++;
			}
			continue ;
		}
		if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&tokens, create_token(TOKEN_REDIR_HEREDOC, ft_strdup("<<")));
				i += 2;
			}
			else
			{
				add_token(&tokens, create_token(TOKEN_REDIR_IN, ft_strdup("<")));
				i++;
			}
			continue ;
		}
		word = extract_word(input, &i);
		if (!word)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token(&tokens, create_token(TOKEN_WORD, word));
	}
	return (tokens);
}
