# Program name
NAME = minishell

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# get_next_line
GNL_DIR = src/get_next_line

GNL_SRC = $(GNL_DIR)/get_next_line.c \
          $(GNL_DIR)/get_next_line_utils.c

# Sources
SRC =	src/main/main.c\
	src/main/prompt.c\
	src/main/history.c\
	src/signals/signals.c\
	src/lexer/lexer.c\
	src/lexer/utils_lexer.c\
	src/parser/parser.c\
	src/parser/parse_pipe.c\
	src/parser/parse_cmd.c\
	src/parser/utils_cmd.c\
	src/parser/translation_function.c\
	src/executor/executor.c\
	src/expander/expander_quotes.c\
	src/expander/expander_variables.c\
	src/expander/expander.c\
	src/built_ins/cd.c\
	src/built_ins/builtins.c\
	src/built_ins/echo.c\
	src/built_ins/env.c\
	src/built_ins/exit.c\
	src/built_ins/export.c\
	src/built_ins/first_utils_export.c\
	src/built_ins/second_utils_export.c\
	src/built_ins/pwd.c\
	src/built_ins/unset.c\
	$(GNL_SRC)

# Objects
OBJS = $(SRC:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE = -lreadline

# Includes
INC = -Ilibft -Iinclude -Isrc/get_next_line -Isrc/signals -Isrc/lexer -Isrc/parser -Isrc/executor -Isrc/expander -Isrc/built_ins -Isrc/main

# Default rule
all: $(LIBFT) $(NAME)

# Build program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f .minishell_history

# Recompile
re: fclean all

.PHONY: all clean fclean re
