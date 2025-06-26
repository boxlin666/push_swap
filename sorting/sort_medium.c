/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:54:53 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:44:58 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_index(t_stack *stack_a)
{
	t_node	*p;
	int		min_num;
	int		index;
	int		min_index;

	p = stack_a->head;
	min_num = p->value;
	index = 0;
	min_index = 0;
	while (p != NULL)
	{
		if (p->value < min_num)
		{
			min_num = p->value;
			min_index = index;
		}
		p = p->next;
		index++;
	}
	return (min_index);
}

void	rotate_to_position(t_stack *stack, int min_index,
		t_operation **operations)
{
	int	size;
	int	forward_steps;
	int	backward_steps;

	if (stack->size == 0 || min_index == 0)
		return ;
	size = stack->size;
	forward_steps = min_index;
	backward_steps = size - min_index;
	if (forward_steps <= backward_steps)
	{
		while (forward_steps--)
			do_ra(stack, operations);
	}
	else
	{
		while (backward_steps--)
			do_rra(stack, operations);
	}
}

void	sort_medium(t_context *ctx)
{
	int	min_index;

	while (ctx->stack_a->size > 3)
	{
		min_index = get_min_index(ctx->stack_a);
		rotate_to_position(ctx->stack_a, min_index, &ctx->operations);
		do_pb(ctx->stack_a, ctx->stack_b, &ctx->operations);
	}
	sort_small(ctx);
	while (ctx->stack_b->size > 0)
	{
		do_pa(ctx->stack_a, ctx->stack_b, &ctx->operations);
	}
}
