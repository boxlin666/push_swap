/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:32 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 14:58:23 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"
#include<stdlib.h>

t_stack *init_stack(void)
{
    t_stack *stack;
    stack = malloc(sizeof(t_stack));
    if (!stack)
        return (NULL);
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    return (stack);
}