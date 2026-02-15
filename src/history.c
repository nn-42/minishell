#include "minishell.h"

static t_list	*g_history = NULL;
static int		g_hist_size = 0;

static void	pop_oldest_history(void)
{
	t_list	*old;

	if (!g_history)
		return ;
	old = g_history;
	g_history = g_history->next;
	ft_lstdelone(old, free);
	g_hist_size--;
}

void	add_to_history(const char *input)
{
	t_list	*new;
	t_list  *tmp;

	if (!input || is_empty_input(input))
		return ;
	new = ft_lstnew(ft_strdup(input));
	if (!new)
		return ;
	ft_lstadd_back(&g_history, new);
	g_hist_size++;
	if (g_hist_size > MAX_HISTORY)
	{
		pop_oldest_history();
		rl_clear_history();
		tmp = g_history;
		while (tmp)
		{
			add_history((char *)tmp->content);
			tmp = tmp->next;
		}
	}
	else
		add_history((char *)input);
}

void	save_history(void)
{
	int		fd;
	t_list	*tmp;

	fd = open(HISTORY_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	tmp = g_history;
	while (tmp)
	{
		write(fd, tmp->content, ft_strlen(tmp->content));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	close(fd);
}

static void	load_history(void)
{
	int		fd;
	char	*line;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (*line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		add_to_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_history(void)
{
	ft_lstclear(&g_history, free);
	g_hist_size = 0;
	rl_clear_history();
	load_history();
}
