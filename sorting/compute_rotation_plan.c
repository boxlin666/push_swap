/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rotation_plan.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:03:51 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 15:24:42 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	find_best_strategy(int *plans, int *min_val, int *strategy)
{
	*min_val = plans[0];
	*strategy = 0;
	if (plans[1] < *min_val)
	{
		*min_val = plans[1];
		*strategy = 1;
	}
	if (plans[2] < *min_val)
	{
		*min_val = plans[2];
		*strategy = 2;
	}
	if (plans[3] < *min_val)
	{
		*min_val = plans[3];
		*strategy = 3;
	}
}

t_rotation_plan	compute_rotation_plan(t_pair idx, t_pair size, int a_val,
		int b_val)
{
	t_rotation_plan	best;
	int				plans[4];
	int				min_val;

	best.ra = idx.a;
	best.rra = size.a - idx.a;
	best.rb = idx.b;
	best.rrb = size.b - idx.b;
	plans[0] = ft_max(best.ra, best.rb);
	plans[1] = ft_max(best.rra, best.rrb);
	plans[2] = best.ra + best.rrb;
	plans[3] = best.rra + best.rb;
	find_best_strategy(plans, &min_val, &best.strategy);
	best.a_idx = idx.a;
	best.b_idx = idx.b;
	best.total = min_val + 2 * ft_max(a_val, b_val) - a_val - b_val;
	return (best);
}
