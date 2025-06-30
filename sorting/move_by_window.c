/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:25:10 by helin             #+#    #+#             */
/*   Updated: 2025/06/30 19:01:51 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_by_window(t_context *ctx, int window_size)
{
	int	start;
	int	pushed;

	start = 0;
	pushed = 0;
	while (ctx->stack_a->size > 0)
	{
		if (ctx->stack_a->head->value < start)
		{
			do_pb(ctx);
			pushed++;
			do_rb(ctx);
		}
		else if (ctx->stack_a->head->value >= start + window_size)
			do_ra(ctx);
		else
		{
			do_pb(ctx);
			pushed++;
			if (ctx->stack_b->head->value < start + window_size / 2)
				do_rb(ctx);
		}
		if (pushed == window_size)
		{
			start += window_size;
			pushed = 0;
		}
	}
}
