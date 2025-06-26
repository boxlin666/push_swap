/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:01:18 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:55:33 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_val_of_idx(t_stack *stack, int index)
{
	t_node	*current;
	int		step;

	current = stack->head;
	step = 0;
	while (step++)
	{
		if (step == index)
			return (current->value);
		current = current->next;
	}
	return (0);
}

int	get_target_index(t_stack *stack_a, int value)
{
	int		min_val;
	int		max_val;
	int		min_index;
	int		i;
	t_node	*node;
	t_node	*next;

	if (stack_a->size == 0)
		return (0);
	min_val = __INT_MAX__;
	max_val = -__INT_MAX__;
	min_index = 0;
	i = 0;
	node = stack_a->head;
	while (node)
	{
		if (node->value < min_val)
		{
			min_val = node->value;
			min_index = i;
		}
		if (node->value > max_val)
			max_val = node->value;
		node = node->next;
		i++;
	}
	if (value < min_val || value > max_val)
		return (min_index);
	node = stack_a->head;
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

t_rotation_plan	find_best_rotation_plan(t_stack *stack_a, t_stack *stack_b)
{
	int				b_idx;
	t_node			*current;
	t_rotation_plan	current_plan;
	t_rotation_plan	best_plan;

	b_idx = 0;
	current = stack_b->head;
	int a_idx, a_val;
	while (current)
	{
		a_idx = get_target_index(stack_a, current->value);
		a_val = get_val_of_idx(stack_a, a_idx);
		current_plan = compute_rotation_plan(a_idx, b_idx, stack_a->size,
				stack_b->size, a_val, current->value);
		if (b_idx == 0 || current_plan.total < best_plan.total)
			best_plan = current_plan;
		current = current->next;
		b_idx++;
	}
	return (best_plan);
}

void	execute_rotation_plan(t_context *ctx, t_rotation_plan plan)
{
	if (plan.strategy == 0)
	{
		while (plan.ra-- > 0)
			do_ra(ctx);
		while (plan.rb-- > 0)
			do_rb(ctx);
	}
	else if (plan.strategy == 1)
	{
		while (plan.rra-- > 0)
			do_rra(ctx);
		while (plan.rrb-- > 0)
			do_rrb(ctx);
	}
	else if (plan.strategy == 2)
	{
		while (plan.ra-- > 0)
			do_ra(ctx);
		while (plan.rrb-- > 0)
			do_rrb(ctx);
	}
	else if (plan.strategy == 3)
	{
		while (plan.rra-- > 0)
			do_rra(ctx);
		while (plan.rb-- > 0)
			do_rb(ctx);
	}
}

void	move_next_element(t_context *ctx)
{
	t_rotation_plan best_plan;

	best_plan = find_best_rotation_plan(ctx->stack_a, ctx->stack_b);
	execute_rotation_plan(ctx, best_plan);
	do_pa(ctx);
}
