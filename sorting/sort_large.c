/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:45:23 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

int	get_chunk_count(int size)
{
	if (size <= 100)
		return (2);
	else
		return (4);
}

void	sort_large(t_context *ctx)
{
	int	num_chunks;
	int	chunk_size;
	int	max_size;
	int	i;
	int	head_value;

	num_chunks = get_chunk_count(ctx->stack_a->size);
	chunk_size = ctx->stack_a->size / num_chunks;
	max_size = ctx->stack_a->size;
	i = 0;
	while (i < num_chunks)
	{
		if (i != num_chunks - 1)
			slice_stack(ctx->stack_a, ctx->stack_b, &ctx->operations, i * chunk_size, (i + 1)
				* chunk_size);
		else
			slice_stack(ctx->stack_a, ctx->stack_b, &ctx->operations, i * chunk_size, max_size);
		i++;
	}
	while (ctx->stack_b->size > 0)
	{
		if (ctx->stack_a->size == 0)
			do_pa(ctx->stack_a, ctx->stack_b, &ctx->operations);
		else if (ctx->stack_a->size == 1)
		{
			do_pa(ctx->stack_a, ctx->stack_b, &ctx->operations);
			if (ctx->stack_a->head->value > ctx->stack_a->tail->value)
				do_sa(ctx);
		}
		else
			move_next_element(ctx->stack_a, ctx->stack_b, &ctx->operations);
	}
	head_value = ctx->stack_a->head->value;
	if (head_value < ctx->stack_a->size / 2)
	{
		while (head_value--)
			do_rra(ctx->stack_a, &ctx->operations);
	}
	else
	{
		head_value = ctx->stack_a->size - head_value;
		while (head_value--)
			do_ra(ctx->stack_a, &ctx->operations);
	}
}
