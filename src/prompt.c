#include "minishell.h"

bool	is_empty_input(const char *input)
{
	int	i;

	if (!input || !*input)
		return (true);
	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static char	*get_prompt(void)
{	
	if (isatty(STDIN_FILENO))
	{
		return ("minishell$ ");
	}
	return ("");
}

char	*read_input(void)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt();
	input = readline(prompt);
	return (input);
}
