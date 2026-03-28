NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

GNL_DIR = src/get_next_line

GNL_SRC = $(GNL_DIR)/get_next_line.c \
          $(GNL_DIR)/get_next_line_utils.c

SRC =	src/main.c\
	src/prompt.c\
	src/history.c\
	src/signals.c\
	src/lexer.c\
	src/lexer_utils.c\
	src/parser.c\
	src/executor.c\
	src/expander.c\
	src/builtins.c\
	src/echo.c\
	src/pwd.c\
	src/cd.c\
	src/exit.c\
	src/env.c\
	src/export.c\
	src/unset.c\
	$(GNL_SRC)

OBJS = $(SRC:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

READLINE = -lreadline

INC = -Ilibft -Iinclude -Isrc/get_next_line

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f .minishell_history

re: fclean all

.PHONY: all clean fclean re
