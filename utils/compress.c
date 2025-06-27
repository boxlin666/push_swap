/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:34:15 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 16:06:34 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	is_rotate_op(const char *op)
{
	return (ft_strncmp(op, "ra", 3) == 0 || ft_strncmp(op, "rb", 3) == 0
		|| ft_strncmp(op, "rb", 3) == 0 || ft_strncmp(op, "rrb", 3) == 0);
}

t_operation	*count_and_free_rotates(t_operation *current, t_rotation_plan *rp)
{
	t_operation	*tmp;

	rp->ra = 0;
	rp->rb = 0;
	rp->rra = 0;
	rp->rrb = 0;
	while (current && is_rotate_op(current->op))
	{
		if (ft_strncmp(current->op, "ra", 3) == 0)
			rp->ra++;
		else if (ft_strncmp(current->op, "rb", 3) == 0)
			rp->rb++;
		else if (ft_strncmp(current->op, "rra", 3) == 0)
			rp->rra++;
		else if (ft_strncmp(current->op, "rrb", 3) == 0)
			rp->rrb++;
		tmp = current;
		current = current->next;
		free(tmp->op);
		free(tmp);
	}
	return (current);
}

void	append_multiple_ops(t_operation **head, t_operation **tail,
		const char *op, int count)
{
	while (count > 0)
	{
		append_op(head, tail, op);
		count--;
	}
}

void	merge_rotates(t_operation **head, t_operation **tail,
		t_rotation_plan rp)
{
	int	rr;
	int	rrr;

	rr = ft_min(rp.ra, rp.rb);
	rp.ra -= rr;
	rp.rb -= rr;
	append_multiple_ops(head, tail, "rr", rr);
	append_multiple_ops(head, tail, "ra", rp.ra);
	append_multiple_ops(head, tail, "rb", rp.rb);
	rrr = ft_min(rp.rra, rp.rrb);
	rp.rra -= rrr;
	rp.rrb -= rrr;
	append_multiple_ops(head, tail, "rrr", rrr);
	append_multiple_ops(head, tail, "rra", rp.rra);
	append_multiple_ops(head, tail, "rrb", rp.rrb);
}

t_operation	*compress_operations(t_operation *head, t_rotation_plan rp)
{
	t_operation	*new_head;
	t_operation	*new_tail;
	t_operation	*current;
	t_operation	*tmp;

	new_head = NULL;
	new_tail = NULL;
	current = head;
	while (current)
	{
		if (is_rotate_op(current->op))
		{
			current = count_and_free_rotates(current, &rp);
			merge_rotates(&new_head, &new_tail, rp);
		}
		else
		{
			append_op(&new_head, &new_tail, current->op);
			tmp = current;
			current = current->next;
			free(tmp->op);
			free(tmp);
		}
	}
	return (new_head);
}
