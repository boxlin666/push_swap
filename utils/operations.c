/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:54:53 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 17:59:50 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

t_operation	*add_operation(t_operation *head, const char *op)
{
	t_operation	*new_op;
	t_operation	*tmp;

	new_op = malloc(sizeof(t_operation));
	new_op->op = ft_strdup(op);
	new_op->next = NULL;
	if (!head)
		return (new_op);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_op;
	return (head);
}

void	append_op(t_operation **head, t_operation **tail, const char *op)
{
	t_operation	*new_op;

	new_op = malloc(sizeof(t_operation));
	new_op->op = ft_strdup(op);
	new_op->next = NULL;
	if (!new_op)
		return ;
	if (!*head)
	{
		*head = new_op;
		*tail = new_op;
	}
	else
	{
		(*tail)->next = new_op;
		*tail = new_op;
	}
}

void	print_operations(t_operation *operations)
{
	t_operation	*tmp;

	tmp = operations->next;
	while (tmp)
	{
		write(1, tmp->op, strlen(tmp->op));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void	free_operations(t_operation *operations)
{
	t_operation	*tmp;

	while (operations)
	{
		tmp = operations;
		operations = operations->next;
		free(tmp->op);
		free(tmp);
	}
}
