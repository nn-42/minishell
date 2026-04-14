/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 07:21:15 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:39:31 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exec(t_exec *exec_ctx, char **envp)
{
	exec_ctx->envp = dup_env(envp);
	if (!exec_ctx->envp)
	{
		error_msg("Fatal", NULL, "failed to initialize environment");
		return (0);
	}
	exec_ctx->last_exit = 0;
	setup_signals();
	init_history();
	return (1);
}

int	handle_input(char **input)
{
	*input = read_input();
	if (!*input)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		return (0);
	}
	if (is_empty_input(*input))
	{
		free(*input);
		return (2);
	}
	if (isatty(STDIN_FILENO))
		add_to_history(*input);
	return (1);
}

void	process_line(char *input, t_exec *exec_ctx)
{
	t_token	*tokens;
	t_ast	*ast;
	t_cmd	*cmd_list;

	tokens = lexer(input);
	free(input);
	if (!tokens)
	{
		exec_ctx->last_exit = 2;
		return ;
	}
	ast = parser(tokens);
	free_tokens(tokens);
	if (!ast)
	{
		exec_ctx->last_exit = 2;
		return ;
	}
	if (expander(ast, exec_ctx))
		return (free_ast(ast));
	cmd_list = ast_to_cmd_list(ast);
	free_ast(ast);
	if (cmd_list)
		execute_pipeline(cmd_list, exec_ctx);
	free_cmd_list(cmd_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec_ctx;
	char	*input;
	int		status;

	(void)argc;
	(void)argv;
	if (!init_exec(&exec_ctx, envp))
		return (1);
	while (1)
	{
		status = handle_input(&input);
		if (status == 0)
			break ;
		if (status == 2)
			continue ;
		process_line(input, &exec_ctx);
	}
	save_history();
	free_env(exec_ctx.envp);
	rl_clear_history();
	free_history();
	return (exec_ctx.last_exit);
}

