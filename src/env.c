#include "minishell.h"

int	builtin_env(char **args, t_exec *exec_ctx)
{
	int	i;

	if (args[1])
	{
		printf("env: too many arguments\n");
		return (1);
	}
	i = 0;
	while (exec_ctx->envp[i])
	{
		printf("%s\n", exec_ctx->envp[i]);
		i++;
	}
	return (0);
}
