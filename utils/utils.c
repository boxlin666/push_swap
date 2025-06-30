/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:59:02 by helin             #+#    #+#             */
/*   Updated: 2025/06/30 15:05:19 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdlib.h"
#include <stdio.h>

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
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

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (stack->size <= 1)
		return (1);
	current = stack->head;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

void print_stacks(t_stack *stack_a, t_stack *stack_b)
{
    t_node *a = stack_a->head;
    t_node *b = stack_b->head;

    printf("\n%-10s %-10s\n", "Stack A", "Stack B");
    printf("----------------------\n");

    // 同时遍历两个栈，逐行打印
    while (a || b)
    {
        if (a)
        {
            printf("%-10d ", a->value);
            a = a->next;
        }
        else
        {
            printf("%-10s ", " ");
        }

        if (b)
        {
            printf("%-10d", b->value);
            b = b->next;
        }
        else
        {
            printf("%-10s", " ");
        }

        printf("\n");
    }

    printf("----------------------\n");
    printf("Size A: %d, Size B: %d\n\n", stack_a->size, stack_b->size);
}
