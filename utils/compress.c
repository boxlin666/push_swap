/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:34:15 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 16:44:33 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	is_rotate_op(const char *op)
{
	return (strcmp(op, "ra") == 0 || strcmp(op, "rb") == 0 || strcmp(op,
			"rra") == 0 || strcmp(op, "rrb") == 0);
}

t_operation	*count_and_free_rotates(t_operation *current, int *ra, int *rb,
		int *rra, int *rrb)
{
	t_operation	*tmp;

	*ra = *rb = *rra = *rrb = 0;
	while (current && is_rotate_op(current->op))
	{
		if (strcmp(current->op, "ra") == 0)
			(*ra)++;
		else if (strcmp(current->op, "rb") == 0)
			(*rb)++;
		else if (strcmp(current->op, "rra") == 0)
			(*rra)++;
		else if (strcmp(current->op, "rrb") == 0)
			(*rrb)++;
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

void	merge_rotates(t_operation **head, t_operation **tail, int ra, int rb,
		int rra, int rrb)
{
	int	rr;
	int	rrr;

	rr = (ra < rb) ? ra : rb;
	ra -= rr;
	rb -= rr;
	append_multiple_ops(head, tail, "rr", rr);
	append_multiple_ops(head, tail, "ra", ra);
	append_multiple_ops(head, tail, "rb", rb);
	rrr = (rra < rrb) ? rra : rrb;
	rra -= rrr;
	rrb -= rrr;
	append_multiple_ops(head, tail, "rrr", rrr);
	append_multiple_ops(head, tail, "rra", rra);
	append_multiple_ops(head, tail, "rrb", rrb);
}

t_operation	*compress_operations(t_operation *head)
{
	t_operation	*new_head;
	t_operation	*new_tail;
	t_operation	*current;
	t_operation	*tmp;

	new_head = NULL;
	new_tail = NULL;
	current = head;
	while (current)
		if (is_rotate_op(current->op))
		{
			int ra, rb, rra, rrb;
			current = count_and_free_rotates(current, &ra, &rb, &rra, &rrb);
			merge_rotates(&new_head, &new_tail, ra, rb, rra, rrb);
		}
		else
		{
			append_op(&new_head, &new_tail, current->op);
			tmp = current;
			current = current->next;
			free(tmp->op);
			free(tmp);
		}
	return (new_head);
}
