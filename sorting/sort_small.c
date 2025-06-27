/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:54:08 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 17:28:33 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_context *ctx)
{
	if (ctx->stack_a->head->value > ctx->stack_a->head->next->value)
		do_sa(ctx);
}

void	sort_three(t_context *ctx)
{
	int	a;
	int	b;
	int	c;

	a = ctx->stack_a->head->value;
	b = ctx->stack_a->head->next->value;
	c = ctx->stack_a->head->next->next->value;
	if (a > b && b < c && a < c)
		do_sa(ctx);
	else if (a > b && b > c && a > c)
	{
		do_sa(ctx);
		do_rra(ctx);
	}
	else if (a < b && b > c && a > c)
		do_rra(ctx);
	else if (a < b && b > c && a < c)
	{
		do_sa(ctx);
		do_ra(ctx);
	}
	else if (a > b && b < c && a > c)
		do_ra(ctx);
}

void	sort_small(t_context *ctx)
{
	if (ctx->stack_a->size == 2)
		sort_two(ctx);
	else if (ctx->stack_a->size == 3)
		sort_three(ctx);
}
