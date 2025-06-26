/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:38:34 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:48:35 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_rra(t_context *ctx)
{
	t_node	*last;

	if (ctx->stack_a->size < 2)
		return ;
	last = ctx->stack_a->tail;
	ctx->stack_a->tail = last->prev;
	ctx->stack_a->tail->next = NULL;
	last->prev = NULL;
	last->next = ctx->stack_a->head;
	ctx->stack_a->head->prev = last;
	ctx->stack_a->head = last;
	ctx->operations = add_operation(ctx->operations, "rra");
}

void	do_rrb(t_context *ctx)
{
	t_node	*last;

	if (ctx->stack_b->size < 2)
		return ;
	last = ctx->stack_b->tail;
	ctx->stack_b->tail = last->prev;
	ctx->stack_b->tail->next = NULL;
	last->prev = NULL;
	last->next = ctx->stack_b->head;
	ctx->stack_b->head->prev = last;
	ctx->stack_b->head = last;
	ctx->operations = add_operation(ctx->operations, "rrb");
}

void	do_rrr(t_context *ctx)
{
	do_rra(ctx);
	do_rrb(ctx);
}
