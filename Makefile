# Program name
NAME = minishell

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Sources
SRC = src/minishell.c src/signals.c

# Objects
OBJS = $(SRC:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE = -lreadline

# Includes
INC = -Ilibft -Iinclude

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

# Recompile
re: fclean all

.PHONY: all clean fclean re