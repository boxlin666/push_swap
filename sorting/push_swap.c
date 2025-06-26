/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:58:41 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:36:44 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	push_swap(t_context *ctx)
{
	if (is_sorted(ctx->stack_a))
		return ;
	if (ctx->stack_a->size <= 3)
		sort_small(ctx->stack_a, &ctx->operations);
	else if (ctx->stack_a->size <= 5)
		sort_medium(ctx->stack_a, ctx->stack_b, &ctx->operations);
	else
		sort_large(ctx);
}
