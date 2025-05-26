/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:54:08 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 15:24:34 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"
#include<unistd.h>

void sort_small(t_stack *stack_a, t_operation **operations)
{
    if (stack_a->size == 2)
    {
        if (stack_a->head->value > stack_a->head->next->value)
            do_sa(stack_a, operations);
    }
    else if (stack_a->size == 3)
    {
        int a = stack_a->head->value;
        int b = stack_a->head->next->value;
        int c = stack_a->head->next->next->value;
        if (a > b && b < c && a < c) // 2,1,3
            do_sa(stack_a, operations);
        else if (a > b && b > c && a > c) // 3,2,1
        {
            do_sa(stack_a, operations);
            do_rra(stack_a, operations);
        }
        else if (a < b && b > c && a > c) // 2,3,1
        {
            do_rra(stack_a, operations);
        }
        else if (a < b && b > c && a < c) // 1,3,2
        {
            do_sa(stack_a, operations);
            do_ra(stack_a, operations);
        }
        else if (a > b && b < c && a > c) // 3,1,2
        {
            do_ra(stack_a, operations);
        }
    }
}
