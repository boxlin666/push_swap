/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/30 19:18:02 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	get_chunk_count(int size)
{
	if (size <= 100)
		return (2);
	else
		return (4);
}

static void	process_chunks(t_context *ctx, int num_chunks, t_pair chunk_meta)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (i < num_chunks)
	{
		start = i * chunk_meta.a;
		if (i != num_chunks - 1)
			end = (i + 1) * chunk_meta.a;
		else
			end = chunk_meta.b;
		slice_stack(ctx, start, end);
		i++;
	}
}

static void	move_all_back(t_context *ctx)
{
	while (ctx->stack_b->size > 0)
	{
		if (ctx->stack_a->size == 0)
			do_pa(ctx);
		else if (ctx->stack_a->size == 1)
		{
			do_pa(ctx);
			if (ctx->stack_a->head->value > ctx->stack_a->tail->value)
				do_sa(ctx);
		}
		else
			move_next_element(ctx);
	}
}

static void	rotate_a_to_min(t_context *ctx)
{
	int	head;
	int	size;

	head = ctx->stack_a->head->value;
	size = ctx->stack_a->size;
	if (head < size / 2)
		while (head--)
			do_rra(ctx);
	else
	{
		head = size - head;
		while (head--)
			do_ra(ctx);
	}
}

void	sort_large(t_context *ctx)
{
	t_pair	chunk_meta;
	int		num_chunks;

	if (ctx->stack_a->size <= 100)
	{
		num_chunks = 2;
		chunk_meta.a = ctx->stack_a->size / num_chunks;
		chunk_meta.b = ctx->stack_a->size;
		process_chunks(ctx, num_chunks, chunk_meta);
	}
	else
	{
		move_by_window(ctx, 125);
	}
	move_all_back(ctx);
	rotate_a_to_min(ctx);
}
