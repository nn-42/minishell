#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_exec exec_ctx;
    char   *input;
    t_token *tokens;
    t_ast   *ast;
    t_cmd   *cmd_list;

    (void)argc;
    (void)argv;

    // تهيئة البيئة (استخدم dup_env لو شغال عندك، أو envp للتجربة)
    exec_ctx.envp = dup_env(envp);
    if (!exec_ctx.envp)
    {
        fprintf(stderr, "Fatal: failed to initialize environment\n");
        return (1);
    }
    exec_ctx.last_exit = 0;

    signals();
    init_history();

    while (1)
    {
        // قراءة الإدخال
        input = read_input();
        if (!input)
        {
            if (isatty(STDIN_FILENO))
                printf("exit\n");
            break;
        }
        if (is_empty_input(input))
        {
            free(input);
            continue;
        }
        if (isatty(STDIN_FILENO))
            add_to_history(input);

        // 1. Lexer
        tokens = lexer(input);
        free(input);
        if (!tokens)
            continue;

        // 2. Parser
        ast = parser(tokens);
        free_tokens(tokens);
        if (!ast)
            continue;

        // 🔥 START: EXPANDER هنا
        if (expander(ast, &exec_ctx))
        {
            free_ast(ast);
            continue;
        }

        // 3. تحويل AST → قائمة أوامر
        cmd_list = ast_to_cmd_list(ast);
        free_ast(ast);
        if (!cmd_list)
            continue;

        // 4. Executor
        if (cmd_list->args && cmd_list->args[0])
            execute_pipeline(cmd_list, &exec_ctx);

        // تنظيف
        free_cmd_list(cmd_list);
    }

    save_history();
    free_env(exec_ctx.envp);
    return exec_ctx.last_exit;
}
