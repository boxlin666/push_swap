/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rotation_plan.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:03:51 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:04:48 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	calculate_rotations(int a_idx, int b_idx, int size_a, int size_b,
		int *ra, int *rra, int *rb, int *rrb)
{
	*ra = a_idx;
	*rra = size_a - a_idx;
	*rb = b_idx;
	*rrb = size_b - b_idx;
}

static void	compute_plan_options(int ra, int rra, int rb, int rrb, int *plans)
{
	plans[0] = ft_max(ra, rb);
	plans[1] = ft_max(rra, rrb);
	plans[2] = ra + rrb;
	plans[3] = rra + rb;
}

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

t_rotation_plan	compute_rotation_plan(int a_idx, int b_idx, int size_a,
		int size_b, int a_val, int b_val)
{
	t_rotation_plan	best;
	int				plans[4];

	int ra, rra, rb, rrb;
	int min_val, strat;
	calculate_rotations(a_idx, b_idx, size_a, size_b, &ra, &rra, &rb, &rrb);
	compute_plan_options(ra, rra, rb, rrb, plans);
	find_best_strategy(plans, &min_val, &strat);
	best.a_idx = a_idx;
	best.b_idx = b_idx;
	best.ra = ra;
	best.rra = rra;
	best.rb = rb;
	best.rrb = rrb;
	best.total = min_val + 2 * ft_max(a_val, b_val) - a_val - b_val;
	best.strategy = strat;
	return (best);
}
