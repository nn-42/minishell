/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 08:48:58 by nnasered          #+#    #+#             */
/*   Updated: 2026/03/09 07:21:06 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	rl_catch_signals = 0;
	init_history();
	signals();
	while (1)
	{
		input = read_input();
		if (!input)
		{
			printf("exit\n");
			break ;
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

/*#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
    char *res;

    res = ft_strjoin(s1, s2);
    free(s1);
    return res;
}

void ft_free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}


static char *find_in_path(char *cmd, char **envp)
{
    (void)envp;
    char *path = getenv("PATH");
    char **dirs;
    char *full;
    int i;

    if (!path)
        return NULL;
    dirs = ft_split(path, ':');
    if (!dirs)
        return NULL;
    i = 0;
    while (dirs[i])
    {
        full = ft_strjoin(dirs[i], "/");
        full = ft_strjoin_free(full, cmd);
        if (access(full, X_OK) == 0)
        {
            ft_free_split(dirs);
            return full;
        }
        free(full);
        i++;
    }
    ft_free_split(dirs);
    return NULL;
}


void executor(t_ast *node, t_exec *exec)
{
    pid_t pid;
    int status;
    char *path;

    if (!node || !node->args || !node->args[0])
        return;

    // Debug: print expanded args
    printf("Executing command:\n");
    for (int i = 0; node->args[i]; i++)
        printf("  arg[%d] = [%s]\n", i, node->args[i]);

    // PATH resolution
    if (node->args[0][0] == '/' || node->args[0][0] == '.')
        path = node->args[0];
    else
        path = find_in_path(node->args[0], exec->envp);

    if (!path)
    {
        fprintf(stderr, "minishell: command not found: %s\n", node->args[0]);
        exec->last_exit = 127;
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        execve(path, node->args, exec->envp);
        perror("execve");
        _exit(127);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            exec->last_exit = WEXITSTATUS(status);
    }
    else
    {
        perror("fork");
    }
    if (path != node->args[0])
        free(path);
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_token *tokens;
    t_ast   *ast;
    t_exec  exec;

    (void)argc;
    (void)argv;

    exec.envp = envp;
    exec.last_exit = 0;

    while (1)
    {
        line = readline(PROMPT);
        if (!line) // ctrl-D
            break;
        if (*line)
            add_history(line);

        // 1. Lexer
        tokens = lexer(line);
        if (!tokens)
        {
            free(line);
            continue;
        }

        // 2. Parser
        ast = parser(tokens);
        free_tokens(tokens);
        if (!ast)
        {
            free(line);
            continue;
        }

        // 3. Expander
        if (expander(ast, &exec) != 0)
        {
            free_ast(ast);
            free(line);
            continue;
        }

        // 4. Executor (بسيط للتجربة)
        executor(ast, &exec);

        free_ast(ast);
        free(line);
    }
    return 0;
}
*/

/*
int	main(void)
{
	char	*input;

	rl_catch_signals = 0;
	init_history();
	signals();
	while (1)
	{
		input = read_input();
		if (!input)
		{
			printf("exit\n");
			break ;
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
}*/

/*
int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;
	bool	levels[10] = {false}; // مصفوفة لتتبع مستويات AST

	init_history();
	signals(); // setup signals

	while (1)
	{
		input = read_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (is_empty_input(input))
		{
			free(input);
			continue ;
		}

		add_to_history(input);

		printf("\n%s════════════════════════════════════════════%s\n", 
			"\033[1;35m", "\033[0m");
		printf("%s📥 INPUT: \"%s\"%s\n", 
			"\033[1;36m", input, "\033[0m");
		printf("%s════════════════════════════════════════════%s\n", 
			"\033[1;35m", "\033[0m");

		// 1️⃣ Lexing
		printf("%s🔰 LEXER OUTPUT (TOKENS):%s\n", "\033[1;33m", "\033[0m");
		tokens = lexer(input);
		if (!tokens)
		{
			printf("❌ Lexer error\n");
			free(input);
			continue ;
		}
		print_tokens(tokens);
		
		// 2️⃣ Parsing
		printf("\n%s🔰 PARSER OUTPUT (AST):%s\n", "\033[1;32m", "\033[0m");
		tree = parser(tokens);
		if (!tree)
		{
			printf("❌ Parser error\n");
			free_tokens(tokens);
			free(input);
			continue ;
		}

		// 3️⃣ Print AST
		print_ast(tree, 0, levels);

		// 4️⃣ Free
		free_ast(tree);
		free_tokens(tokens);
		free(input);
		
		printf("%s────────────────────────────────────────────%s\n\n", 
			"\033[1;30m", "\033[0m");
	}

	save_history();
	return (0);
}
*/