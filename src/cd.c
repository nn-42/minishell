#include "minishell.h"

int	builtin_cd(char **args, t_exec *exec_ctx)
{
	char	*path;
	char	*home;
	char	*old_pwd;
	char	*new_pwd;
	int		index;

	old_pwd = getcwd(NULL, 0);
	if (!args[1])
	{
		index = find_env_var(exec_ctx->envp, "HOME");
		if (index == -1)
		{
			printf("cd: HOME not set\n");
			free(old_pwd);
			return (1);
		}
		home = ft_strchr(exec_ctx->envp[index], '=');
		if (!home)
		{
			free(old_pwd);
			return (1);
		}
		path = home + 1;
	}
	else if (args[2])
	{
		printf("cd: too many arguments\n");
		free(old_pwd);
		return (1);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_var(&exec_ctx->envp, "PWD", new_pwd);
		free(new_pwd);
	}
	if (old_pwd)
	{
		set_env_var(&exec_ctx->envp, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	return (0);
}
