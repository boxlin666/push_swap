/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rotation_plan.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:40:14 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 15:40:48 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	execute_symmetric_rotation(t_context *ctx, t_rotation_plan plan)
{
	if (plan.strategy == 0)
	{
		while (plan.ra-- > 0)
			do_ra(ctx);
		while (plan.rb-- > 0)
			do_rb(ctx);
	}
	else
	{
		while (plan.rra-- > 0)
			do_rra(ctx);
		while (plan.rrb-- > 0)
			do_rrb(ctx);
	}
}

static void	execute_asymmetric_rotation(t_context *ctx, t_rotation_plan plan)
{
	if (plan.strategy == 2)
	{
		while (plan.ra-- > 0)
			do_ra(ctx);
		while (plan.rrb-- > 0)
			do_rrb(ctx);
	}
	else
	{
		while (plan.rra-- > 0)
			do_rra(ctx);
		while (plan.rb-- > 0)
			do_rb(ctx);
	}
}

void	execute_rotation_plan(t_context *ctx, t_rotation_plan plan)
{
	if (plan.strategy == 0 || plan.strategy == 1)
		execute_symmetric_rotation(ctx, plan);
	else
		execute_asymmetric_rotation(ctx, plan);
}
