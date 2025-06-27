/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:58:41 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 17:37:39 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_context *ctx)
{
	if (is_sorted(ctx->stack_a))
		return ;
	if (ctx->stack_a->size <= 3)
		sort_small(ctx);
	else if (ctx->stack_a->size <= 5)
		sort_medium(ctx);
	else
		sort_large(ctx);
}
