/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 08:48:58 by nnasered          #+#    #+#             */
/*   Updated: 2026/02/25 16:39:48 by nfaronia         ###   ########.fr       */
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
}

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