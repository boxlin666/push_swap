/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:38:22 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 17:14:22 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	are_inverse_ops(const char *op1, const char *op2)
{
	return ((ft_strncmp(op1, "ra", 3) == 0 && ft_strncmp(op2, "rra", 3) == 0)
		|| (ft_strncmp(op1, "rra", 3) == 0 && ft_strncmp(op2, "ra", 3) == 0)
		|| (ft_strncmp(op1, "rb", 3) == 0 && ft_strncmp(op2, "rrb", 3) == 0)
		|| (ft_strncmp(op1, "rrb", 3) == 0 && ft_strncmp(op2, "rb", 3) == 0));
}

t_operation	*remove_inverse_pair(t_operation *head, t_operation *prev,
		t_operation *current)
{
	t_operation	*next_node;
	t_operation	*iter;

	next_node = current->next;
	if (prev == head)
	{
		head = next_node;
	}
	else
	{
		iter = head;
		while (iter->next != prev)
			iter = iter->next;
		iter->next = next_node;
	}
	free(prev->op);
	free(prev);
	free(current->op);
	free(current);
	return (head);
}

t_operation	*optimize_operations(t_operation *head)
{
	t_operation	*prev;
	t_operation	*current;

	if (!head || !head->next)
		return (head);
	prev = head;
	current = head->next;
	while (current)
	{
		if (are_inverse_ops(prev->op, current->op))
		{
			head = remove_inverse_pair(head, prev, current);
			if (!head)
				return (NULL);
			prev = head;
			current = head->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (head);
}
