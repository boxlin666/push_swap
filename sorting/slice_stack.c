/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:56:49 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 15:30:49 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_ra_next(t_stack *stack, int min_val, int max_val)
{
	int		step;
	t_node	*cur;

	if (stack->size == 0)
		return (0);
	step = 0;
	cur = stack->head;
	while (cur)
	{
		if (cur->value >= min_val && cur->value < max_val)
			return (step);
		step++;
		cur = cur->next;
	}
	return (0);
}

int	find_rra_next(t_stack *stack, int min_val, int max_val)
{
	int		step;
	t_node	*cur;

	if (stack->size == 0)
		return (0);
	step = 1;
	cur = stack->tail;
	while (cur)
	{
		if (cur->value >= min_val && cur->value < max_val)
			return (-step);
		step++;
		cur = cur->prev;
	}
	return (0);
}

static int	count_slice_targets(t_stack *stack, t_pair range)
{
	int		count;
	t_node	*node;

	count = 0;
	node = stack->head;
	while (node)
	{
		if (node->value >= range.a && node->value < range.b)
			count++;
		node = node->next;
	}
	return (count);
}

static void	move_slice_target(t_context *ctx, t_pair range)
{
	int	fw;
	int	bw;

	fw = find_ra_next(ctx->stack_a, range.a, range.b);
	bw = -1 * find_rra_next(ctx->stack_a, range.a, range.b);
	if (fw <= bw)
		while (fw--)
			do_ra(ctx);
	else
		while (bw--)
			do_rra(ctx);
	do_pb(ctx);
	if (ctx->stack_b->head->value < (range.a + range.b) / 2)
		do_rb(ctx);
}

void	slice_stack(t_context *ctx, int min_val, int max_val)
{
	int	count;

	count = count_slice_targets(ctx->stack_a, (t_pair){min_val, max_val});
	while (count--)
		move_slice_target(ctx, (t_pair){min_val, max_val});
}
