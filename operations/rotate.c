/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:38:12 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:49:19 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_ra(t_context *ctx)
{
	t_node	*first;

	if (ctx->stack_a->size < 2)
		return ;
	first = ctx->stack_a->head;
	ctx->stack_a->head = first->next;
	ctx->stack_a->head->prev = NULL;
	first->next = NULL;
	first->prev = ctx->stack_a->tail;
	ctx->stack_a->tail->next = first;
	ctx->stack_a->tail = first;
	ctx->operations = add_operation(ctx->operations, "ra");
}

void	do_rb(t_context *ctx)
{
	t_node	*first;

	if (ctx->stack_b->size < 2)
		return ;
	first = ctx->stack_b->head;
	ctx->stack_b->head = first->next;
	ctx->stack_b->head->prev = NULL;
	first->next = NULL;
	first->prev = ctx->stack_b->tail;
	ctx->stack_b->tail->next = first;
	ctx->stack_b->tail = first;
	ctx->operations = add_operation(ctx->operations, "rb");
}

void	do_rr(t_context *ctx)
{
	do_ra(ctx);
	do_rb(ctx);
}
