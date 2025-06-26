/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:13:37 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 17:21:37 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void	push_to_stack(t_context *ctx, int value)
{
	t_node	*new_node;
	t_stack	*stack;

	new_node = malloc(sizeof(t_node));
	stack = ctx->stack_a;
	if (!new_node)
		error_exit(ctx);
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = stack->tail;
	if (stack->tail)
		stack->tail->next = new_node;
	else
		stack->head = new_node;
	stack->tail = new_node;
	stack->size++;
}

int	is_valid_number(const char *str, long *result)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	*result = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		*result = *result * 10 + (str[i] - '0');
		if (*result * sign > INT_MAX || *result * sign < INT_MIN)
			return (0);
		i++;
	}
	*result *= sign;
	return (1);
}

int	has_duplicates(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	current = stack->head;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (current->value == next->value)
				return (1);
			next = next->next;
		}
		current = current->next;
	}
	return (0);
}

void	free_split(char **numbers)
{
	int	i;

	i = 0;
	if (!numbers)
		return ;
	while (numbers[i])
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\n' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

char	**split_by_space(const char *str)
{
	int			count = 0, len;
	char		**result;
	const char	*start = NULL;
	int			word_len;
	char		*word;
	char		**temp;

	count = 0, len = strlen(str);
	result = NULL;
	for (int j = 0; j <= len; j++)
	{
		if (!ft_isspace(str[j]) && !start)
			start = &str[j];
		else if ((ft_isspace(str[j]) || str[j] == '\0') && start)
		{
			word_len = &str[j] - start;
			word = malloc(word_len + 1);
			if (!word)
				return (free_split(result), NULL);
			strncpy(word, start, word_len);
			word[word_len] = '\0';
			temp = realloc(result, sizeof(char *) * (count + 2));
			if (!temp)
				return (free_split(result), NULL);
			result = temp;
			result[count++] = word;
			result[count] = NULL;
			start = NULL;
		}
	}
	return (result);
}

int	process_number_list(t_context *ctx, char **list)
{
	int		i;
	long	num;

	i = 0;
	while (list[i])
	{
		if (!is_valid_number(list[i], &num) || num < INT_MIN || num > INT_MAX)
		{
			free_split(list);
			error_exit(ctx);
		}
		push_to_stack(ctx, (int)num);
		i++;
	}
	return (1);
}

int	parse_input(t_context *ctx, int argc, char **argv)
{
	char	**nums;
			long num;

	if (argc < 2)
		return (0);
	if (argc == 2)
	{
		nums = split_by_space(argv[1]);
		if (!nums)
			error_exit(ctx);
		process_number_list(ctx, nums);
		free_split(nums);
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			if (!is_valid_number(argv[i], &num) || num < INT_MIN
				|| num > INT_MAX)
				error_exit(ctx);
			push_to_stack(ctx, (int)num);
		}
	}
	if (has_duplicates(ctx->stack_a))
		error_exit(ctx);
	return (1);
}
