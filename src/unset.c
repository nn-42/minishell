#include "minishell.h"

int	unset_env_var(char ***envp, char *name)
{
	char	**new_env;
	int		index;
	int		count;
	int		i;
	int		j;

	index = find_env_var(*envp, name);
	if (index == -1)
		return (0);
	count = count_env_vars(*envp);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (-1);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != index)
		{
			new_env[j] = (*envp)[i];
			j++;
		}
		else
			free((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}

int	builtin_unset(char **args, t_exec *exec_ctx)
{
	int	i;

	if (!args[1])
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (unset_env_var(&exec_ctx->envp, args[i]) < 0)
		{
			printf("unset: failed to remove %s\n", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
