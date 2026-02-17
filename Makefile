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
	src/parser/futils_parser.c\
	src/parser/parser.c\
	src/parser/sutils_parser.c\
	src/parser/test_parser.c\
	src/lexer/test_lexer.c\
	$(GNL_SRC)

# Objects
OBJS = $(SRC:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE = -lreadline

# Includes
INC = -Ilibft -Iinclude -Isrc/get_next_line

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
