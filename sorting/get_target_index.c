/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_target_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:45:40 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 15:46:15 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"push_swap.h"

static int	get_min_index_and_range(t_stack *stack, int *min, int *max)
{
	t_node	*node;
	int		i;
	int		min_index;

	node = stack->head;
	i = 0;
	min_index = 0;
	*min = __INT_MAX__;
	*max = -__INT_MAX__;
	while (node)
	{
		if (node->value < *min)
		{
			*min = node->value;
			min_index = i;
		}
		if (node->value > *max)
			*max = node->value;
		node = node->next;
		i++;
	}
	return (min_index);
}

int	find_min_and_max(t_stack *stack, t_pair *minmax)
{
	int	min_index;
	int	min;
	int	max;

	min_index = get_min_index_and_range(stack, &min, &max);
	minmax->a = min;
	minmax->b = max;
	return (min_index);
}

static int	find_insert_position(t_stack *stack, int value)
{
	t_node	*node;
	t_node	*next;
	int		i;

	node = stack->head;
	next = node->next;
	i = 1;
	while (next)
	{
		if (node->value < value && value < next->value)
			return (i);
		node = next;
		next = next->next;
		i++;
	}
	return (0);
}

int	get_target_index(t_stack *stack_a, int value)
{
	int		min_index;
	t_pair	minmax;

	if (stack_a->size == 0)
		return (0);
	min_index = find_min_and_max(stack_a, &minmax);
	if (value < minmax.a || value > minmax.b)
		return (min_index);
	return (find_insert_position(stack_a, value));
}
