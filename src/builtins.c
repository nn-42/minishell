#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);

	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);

	return (0);
}

int	execute_builtin(char **args, t_exec *exec_ctx)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, exec_ctx));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, exec_ctx));
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, exec_ctx));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, exec_ctx));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, exec_ctx));
	return (0);
}

void	cleanup_shell(void)
{
	// Clear readline history
	rl_clear_history();

	// TODO: Free any allocated memory (environment, etc.)
	// This will be more important when we implement export/unset
}
