# --- Variables ---
NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# --- Source Files ---
SRCS_DIR = .
SRCS =	main.c \
		parsing.c \
		stack_utils.c \
		operations_swap.c \
		operations_push.c \
		operations_rotate.c \
		operations_rev_rotate.c \
		sort_logic.c

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# --- Libft ---
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I $(LIBFT_DIR)
LIBFT_LNK = -L $(LIBFT_DIR) -lft

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LNK) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c push_swap.h Makefile | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I . $(LIBFT_INC) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

# --- Phony Targets ---
.PHONY: all clean fclean re bonus