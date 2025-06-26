# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helin <helin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 12:10:40 by helin             #+#    #+#              #
#    Updated: 2025/06/26 14:05:18 by helin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iincludes -Ilibft

SRCS_DIR = .
SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/operations/swap.c \
       $(SRCS_DIR)/operations/push.c \
       $(SRCS_DIR)/operations/rotate.c \
       $(SRCS_DIR)/operations/reverse_rotate.c \
       $(SRCS_DIR)/sorting/sort_small.c \
       $(SRCS_DIR)/sorting/sort_medium.c \
       $(SRCS_DIR)/sorting/sort_large.c \
       $(SRCS_DIR)/sorting/slice_stack.c \
       $(SRCS_DIR)/sorting/move_next_element.c \
       $(SRCS_DIR)/sorting/compute_rotation_plan.c \
       $(SRCS_DIR)/sorting/push_swap.c \
       $(SRCS_DIR)/utils/operations.c \
       $(SRCS_DIR)/utils/parse.c \
       $(SRCS_DIR)/utils/error.c \
       $(SRCS_DIR)/utils/memory.c \
       $(SRCS_DIR)/utils/compress.c \
       $(SRCS_DIR)/utils/optimize.c \
       $(SRCS_DIR)/utils/utils.c \
       $(SRCS_DIR)/utils/input.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

BONUS_NAME = checker
BONUS_DIR = bonus
BONUS_SRCS = $(BONUS_DIR)/checker.c \
             $(BONUS_DIR)/checker_utils.c \
             $(SRCS_DIR)/operations/swap.c \
             $(SRCS_DIR)/operations/push.c \
             $(SRCS_DIR)/operations/rotate.c \
             $(SRCS_DIR)/operations/reverse_rotate.c \
             $(SRCS_DIR)/utils/parse.c \
             $(SRCS_DIR)/utils/error.c \
             $(SRCS_DIR)/utils/memory.c \
             $(SRCS_DIR)/utils/helpers.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT)