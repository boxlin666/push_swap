/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:54:53 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 14:00:09 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

t_operation *add_operation(t_operation *head, const char *op)
{
    t_operation *new_op;
    t_operation *tmp;

    new_op = malloc(sizeof(t_operation));
        //error_exit();
    new_op->op = strdup(op);
    if (!new_op->op)
    {
        free(new_op);
        //error_exit();
    }
    new_op->next = NULL;
    if (!head)
        return (new_op);
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_op;
    return (head);
}

void print_operations(t_operation *operations)
{
    t_operation *tmp;

    tmp = operations;
    while (tmp)
    {
        write(1, tmp->op, strlen(tmp->op));
        write(1, "\n", 1);
        tmp = tmp->next;
    }
}

void free_operations(t_operation *operations)
{
    t_operation *tmp;

    while (operations)
    {
        tmp = operations;
        operations = operations->next;
        free(tmp->op);
        free(tmp);
    }
}

t_operation *optimize_operations(t_operation *head)
{
    t_operation *current;
    t_operation *prev;

    if (!head || !head->next)
        return (head);
    prev = head;
    current = head->next;
    while (current)
    {
        if ((strcmp(prev->op, "ra") == 0 && strcmp(current->op, "rra") == 0) ||
            (strcmp(prev->op, "rra") == 0 && strcmp(current->op, "ra") == 0) ||
            (strcmp(prev->op, "rb") == 0 && strcmp(current->op, "rrb") == 0) ||
            (strcmp(prev->op, "rrb") == 0 && strcmp(current->op, "rb") == 0))
        {
            t_operation *temp = current->next;
            if (prev == head)
                head = temp;
            else
            {
                t_operation *prev_prev = head;
                while (prev_prev->next != prev)
                    prev_prev = prev_prev->next;
                prev_prev->next = temp;
            }
            free(prev->op);
            free(prev);
            free(current->op);
            free(current);
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