/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:05:49 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/25 13:07:22 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define COLOR_CMD    "\033[1;32m" // أخضر
#define COLOR_PIPE   "\033[1;33m" // أصفر
#define COLOR_REDIR  "\033[1;34m" // أزرق
#define COLOR_RESET  "\033[0m"

static void print_node_prefix(int level, bool last, bool *levels)
{
    for (int i = 0; i < level; i++)
    {
        if (i == level - 1)
            printf("%s", last ? "└── " : "├── ");
        else
            printf("%s", levels[i] ? "    " : "│   ");
    }
}

static void print_redirs(t_redir *redir, int level, bool *levels)
{
    while (redir)
    {
        print_node_prefix(level, !redir->next, levels);
        if (redir->type == TOKEN_REDIR_IN)
            printf(COLOR_REDIR "REDIR_IN  <  %s\n" COLOR_RESET, redir->filename);
        else if (redir->type == TOKEN_REDIR_OUT)
            printf(COLOR_REDIR "REDIR_OUT >  %s\n" COLOR_RESET, redir->filename);
        else if (redir->type == TOKEN_APPEND)
            printf(COLOR_REDIR "APPEND    >> %s\n" COLOR_RESET, redir->filename);
        else if (redir->type == TOKEN_HEREDOC)
            printf(COLOR_REDIR "HEREDOC   << %s\n" COLOR_RESET, redir->filename);
        redir = redir->next;
    }
}

static void print_args(char **args, int level, bool *levels)
{
    for (int i = 0; args && args[i]; i++)
    {
        print_node_prefix(level, !args[i + 1], levels);
        printf(COLOR_CMD "ARG: %s\n" COLOR_RESET, args[i]);
    }
}

void print_ast(t_ast *node, int level, bool *levels)
{
    if (!node)
        return;

    bool last = true; // افتراض أن العقدة الأخيرة في هذا الفرع
    print_node_prefix(level, last, levels);

    if (node->type == NUDE_PIPE)
    {
        printf(COLOR_PIPE "PIPE\n" COLOR_RESET);

        // حدد مستويات الفروع لتعديل الخطوط العمودية
        bool new_levels[level + 1];
        for (int i = 0; i < level; i++)
            new_levels[i] = levels[i];
        new_levels[level] = false; // PIPE لديه فرع إضافي

        print_ast(node->left, level + 1, new_levels);
        new_levels[level] = true;
        print_ast(node->right, level + 1, new_levels);
    }
    else if (node->type == NODE_CMD)
    {
        printf(COLOR_CMD "CMD\n" COLOR_RESET);
        print_args(node->args, level + 1, levels);
        print_redirs(node->redirs, level + 1, levels);
    }
}