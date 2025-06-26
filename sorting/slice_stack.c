/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:56:49 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 13:59:04 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_ra_next(t_stack *stack, int min_val, int max_val)
{
	int	step;

	if (stack->size == 0)
		return (0);
	step = 0;
	for (t_node *cur = stack->head; cur; cur = cur->next)
	{
		if (cur->value >= min_val && cur->value < max_val)
			return (step);
		step++;
	}
	return (0);
}

int	find_rra_next(t_stack *stack, int min_val, int max_val)
{
	int	step;

	if (stack->size == 0)
		return (0);
	step = 1;
	for (t_node *cur = stack->tail; cur; cur = cur->prev)
	{
		if (cur->value >= min_val && cur->value < max_val)
			return (-step);
		step++;
	}
	return (0);
}

void	slice_stack(t_stack *stack_a, t_stack *stack_b,
		t_operation **operations, int min_val, int max_val)
{
	int	forward_steps;
	int	backward_steps;
	int	count;

	count = 0;
	for (t_node *n = stack_a->head; n; n = n->next)
	{
		if (n->value >= min_val && n->value < max_val)
			count++;
	}
	while (count)
	{
		forward_steps = find_ra_next(stack_a, min_val, max_val);
		backward_steps = -1 * find_rra_next(stack_a, min_val, max_val);
		if (forward_steps <= backward_steps)
			while (forward_steps--)
				do_ra(stack_a, operations);
		else
			while (backward_steps--)
				do_rra(stack_a, operations);
		do_pb(stack_a, stack_b, operations);
		if (stack_b->head->value < (min_val + max_val) / 2)
			do_rb(stack_b, operations);
		count--;
	}
}
