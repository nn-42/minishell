#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	char	*type_names[] = {
		"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", 
		"REDIR_APPEND", "REDIR_HEREDOC", "EOF"
	};

	current = tokens;
	while (current)
	{
		printf("[%s: '%s'] ", type_names[current->type], current->value);
		current = current->next;
	}
	printf("\n");
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;
	t_exec	exec_context;

	(void)argc;
	(void)argv;

	exec_context.envp = dup_env(envp);
	if (!exec_context.envp)
	{
		printf("Fatal: failed to initialize environment\n");
		return (1);
	}
	exec_context.last_exit = 0;

	init_history();
	setup_signals();

	while (1)
	{
		input = read_input();
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (is_empty_input(input))
		{
			free(input);
			continue ;
		}
		////////////////////////
		tokens = tokenize(input);
		if (!tokens)
		{
			printf("Error: unclosed quotes\n");
			free(input);
			continue;
		}
		print_tokens(tokens);

		////parser_test////////
		t_cmd *commands = parse(tokens);
		if (!commands)
		{
			printf("Parsing failed\n");
			free_tokens(tokens);
			free(input);
			continue;
		}
		printf("Parsing successful!\n");
		////expansion_test/////
		expand_commands(commands, &exec_context);
		////execution_test/////
		//execute_simple_cmd(commands, &exec_context);
		execute_pipeline(commands, &exec_context);
		///////////////////////
		add_to_history(input);
		free(input);
		free_tokens(tokens);
		free_commands(commands);
	}
	save_history();
	free_env(exec_context.envp);
	return (0);
}
