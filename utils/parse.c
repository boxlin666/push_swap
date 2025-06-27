/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:13:37 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 16:40:16 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

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
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
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



int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\n' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
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
	long	num;
	int i=0;
	if (argc == 2)
	{
		nums = ft_split(argv[1], ' ');
		if (!nums)
			error_exit(ctx);
		process_number_list(ctx, nums);
		free_split(nums);
	}
	else
	{
		while(i < argc)
		{
			if (!is_valid_number(argv[i++], &num) || num < INT_MIN
				|| num > INT_MAX)
				error_exit(ctx);
			push_to_stack(ctx, (int)num);
		}
	}
	if (has_duplicates(ctx->stack_a))
		error_exit(ctx);
	return (1);
}
