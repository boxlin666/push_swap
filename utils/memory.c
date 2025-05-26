/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:30 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 14:57:04 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"
#include<stdlib.h>

void free_stack(t_stack *stack)
{
    t_node *current;
    t_node *next;
    if (!stack)
        return;
    current = stack->head;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}
