/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:34:17 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:41:00 by helin            ###   ########.fr       */
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

void	do_sb(t_stack *stack_b, t_operation **operations)
{
	t_node	*first;
	t_node	*second;

	if (stack_b->size < 2)
		return ;
	first = stack_b->head;
	second = stack_b->head->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		stack_b->tail = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	stack_b->head = second;
	*operations = add_operation(*operations, "sb");
}

void	do_ss(t_context *ctx)
{
	do_sa(ctx);
	do_sb(ctx->stack_b, &ctx->operations);
}
