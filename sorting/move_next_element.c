/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:01:18 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 15:46:56 by helin            ###   ########.fr       */
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

t_rotation_plan	find_best_rotation_plan(t_stack *stack_a, t_stack *stack_b)
{
	t_pair			idx;
	t_node			*current;
	t_rotation_plan	current_plan;
	t_rotation_plan	best_plan;
	int				a_val;

	idx.b = 0;
	current = stack_b->head;
	while (current)
	{
		idx.a = get_target_index(stack_a, current->value);
		a_val = get_val_of_idx(stack_a, idx.a);
		current_plan = compute_rotation_plan(idx, (t_pair){stack_a->size,
				stack_b->size}, a_val, current->value);
		if (idx.b == 0 || current_plan.total < best_plan.total)
			best_plan = current_plan;
		current = current->next;
		idx.b++;
	}
	return (best_plan);
}

void	move_next_element(t_context *ctx)
{
	t_rotation_plan	best_plan;

	best_plan = find_best_rotation_plan(ctx->stack_a, ctx->stack_b);
	execute_rotation_plan(ctx, best_plan);
	do_pa(ctx);
}
