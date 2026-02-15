#include "minishell.h"

int	main(void)
{
	char	*input;

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
		add_to_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	save_history();
	return (0);
}
