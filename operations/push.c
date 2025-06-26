/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:31:08 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:47:46 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_pa(t_context *ctx)
{
	t_node	*temp;

	if (ctx->stack_b->size == 0)
		return ;
	temp = ctx->stack_b->head;
	ctx->stack_b->head = ctx->stack_b->head->next;
	if (ctx->stack_b->head)
		ctx->stack_b->head->prev = NULL;
	else
		ctx->stack_b->tail = NULL;
	ctx->stack_b->size--;
	temp->next = ctx->stack_a->head;
	temp->prev = NULL;
	if (ctx->stack_a->head)
		ctx->stack_a->head->prev = temp;
	else
		ctx->stack_a->tail = temp;
	ctx->stack_a->head = temp;
	ctx->stack_a->size++;
	ctx->operations = add_operation(ctx->operations, "pa");
}

void	do_pb(t_context *ctx)
{
	t_node	*temp;

	if (ctx->stack_a->size == 0)
		return ;
	temp = ctx->stack_a->head;
	ctx->stack_a->head = ctx->stack_a->head->next;
	if (ctx->stack_a->head)
		ctx->stack_a->head->prev = NULL;
	else
		ctx->stack_a->tail = NULL;
	ctx->stack_a->size--;
	temp->next = ctx->stack_b->head;
	temp->prev = NULL;
	if (ctx->stack_b->head)
		ctx->stack_b->head->prev = temp;
	else
		ctx->stack_b->tail = temp;
	ctx->stack_b->head = temp;
	ctx->stack_b->size++;
	ctx->operations = add_operation(ctx->operations, "pb");
}
