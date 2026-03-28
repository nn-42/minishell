#include "minishell.h"

t_redir	*create_redir(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_redir(t_redir **redirections, t_redir *new)
{
	t_redir	*current;

	if (!*redirections)
	{
		*redirections = new;
		return ;
	}
	current = *redirections;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

char	**add_arg(char **args, char *new_arg)
{
	char	**new_args;
	int		i;
	int		count;

	count = count_args(args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(new_arg);
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

void	free_commands(t_cmd *commands)
{
    t_cmd   *tmp_cmd;
    t_redir *tmp_redir;
    int     i;

    while (commands)
    {
        if (commands->args)
        {
            i = 0;
            while (commands->args[i])
            {
                free(commands->args[i]);
                i++;
            }
            free(commands->args);
        }
        while (commands->redirections)
        {
            tmp_redir = commands->redirections;
            commands->redirections = commands->redirections->next;
            free(tmp_redir->file);
            free(tmp_redir);
        }
        tmp_cmd = commands;
        commands = commands->next;
        free(tmp_cmd);
    }
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*current_cmd;
	t_token	*current_token;

	if (!tokens)
		return (NULL);

	commands = NULL;
	current_cmd = create_cmd();
	if (!current_cmd)
		return (NULL);
	commands = current_cmd;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == TOKEN_PIPE)
		{
				if (!current_cmd->args)
				{
					printf("Error: syntax error near pipe\n");
					free_commands(commands);
					return (NULL);
				}
				t_cmd *new_cmd = create_cmd();
				if (!new_cmd)
				{
					free_commands(commands);
					return (NULL);
				}
				current_cmd->next = new_cmd;
				current_cmd = new_cmd;
		}
		else if (current_token->type >= TOKEN_REDIR_IN
			&& current_token->type <= TOKEN_REDIR_HEREDOC)
		{
				if (!current_token->next || current_token->next->type != TOKEN_WORD)
				{
					printf("Error: syntax error near redirection\n");
					free_commands(commands);
					return (NULL);
				}
				t_redir *new_redir = create_redir(current_token->type,
                                      current_token->next->value);
				if (!new_redir)
				{
					free_commands(commands);
					return (NULL);
				}
				add_redir(&current_cmd->redirections, new_redir);
				current_token = current_token->next;
		}
		else if (current_token->type == TOKEN_WORD)
		{
			current_cmd->args = add_arg(current_cmd->args, current_token->value);
			if (!current_cmd->args)
			{
				free_commands(commands);
				return (NULL);
			}
		}
		current_token = current_token->next;
	}
	if (!current_cmd->args)
	{
		printf("Error: syntax error near pipe\n");
		free_commands(commands);
		return (NULL);
	}
	return (commands);
}
