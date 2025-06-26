/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:34:17 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:50:00 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_sa(t_context *ctx)
{
	t_node	*first;
	t_node	*second;

	if (ctx->stack_a->size < 2)
		return ;
	first = ctx->stack_a->head;
	second = ctx->stack_a->head->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		ctx->stack_a->tail = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	ctx->stack_a->head = second;
	ctx->operations = add_operation(ctx->operations, "sa");
}

void	do_sb(t_context *ctx)
{
	t_node	*first;
	t_node	*second;

	if (ctx->stack_b->size < 2)
		return ;
	first = ctx->stack_b->head;
	second = ctx->stack_b->head->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		ctx->stack_b->tail = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	ctx->stack_b->head = second;
	ctx->operations = add_operation(ctx->operations, "sb");
}

void	do_ss(t_context *ctx)
{
	do_sa(ctx);
	do_sb(ctx);
}
