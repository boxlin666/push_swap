/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/04 20:48:30 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdlib.h>
#include <limits.h>

void td_small_sort(t_stack *stack_a, t_stack *stack_b, int n, t_operation **operations)
{
    int v1, v2, v3;
    if(n == 2)
    {
        if(stack_a->head->value > stack_a->head->next->value)
            do_sa(stack_a,operations);
    }
    else
    {
        v1 = stack_a->head->value;
        v2 = stack_a->head->next->value;
        v3 = stack_a->head->next->next->value;
        if(v1 < v3 && v2 > v3)
        {
            do_ra(stack_a,operations);
            do_sa(stack_a,operations);
            do_rra(stack_a,operations);
        }
        else if(v1 > v2 && v1 < v3)
        {
            do_sa(stack_a,operations);
        }
        else if(v1 < v2 && v1 > v3)
        {
            do_ra(stack_a,operations);
            do_ra(stack_a,operations);
            do_pb(stack_a, stack_b, operations);
            do_rra(stack_a,operations);
            do_rra(stack_a,operations);
            do_pa(stack_a, stack_b, operations);
        }
        else if(v1 > v3 && v2 < v3)
        {
            do_sa(stack_a,operations);
            do_ra(stack_a,operations);
            do_sa(stack_a,operations);
            do_rra(stack_a,operations);
        }
        else if(v1 > v2 && v2 > v3)
        {
            do_sa(stack_a,operations);
            do_ra(stack_a,operations);
            do_ra(stack_a,operations);
            do_pb(stack_a, stack_b, operations);
            do_rra(stack_a,operations);
            do_rra(stack_a,operations);
            do_pa(stack_a, stack_b, operations);
        }
    }
}

void choose_two_pivots(t_stack *stack, int n, int *pivot1, int *pivot2)
{
    int temp[n];
    t_node *cur = stack->head;
    for (int i = 0; i < n && cur; i++, cur = cur->next)
        temp[i] = cur->value;

    quick_sort(temp, 0, n - 1);

    *pivot1 = temp[n / 3];
    *pivot2 = temp[2 * n / 3];
}

void td_quicksort(t_stack *stack_a, t_stack *stack_b, int n, t_operation **operations)
{
    // print_stacks(stack_a, stack_b);
    if(n <= 1)
        return;
    else if(n <= 3)
    {
        td_small_sort(stack_a, stack_b, n, operations);
        return;
    }
    int pivot1;
    int pivot2;
    choose_two_pivots(stack_a, n, &pivot1, &pivot2);
    int t = n;
    int x;
    int count_low = 0;
    int count_mid = 0;
    int count_high = 0;
    while (t--)
    {
        x = stack_a->head->value;
        if(x < pivot1)
        {
            do_pb(stack_a, stack_b, operations);
            do_rb(stack_b, operations);
            count_low++;
        }
        else if(x < pivot2)
        {
            do_pb(stack_a, stack_b, operations);
            count_mid++;
        }
        else
        {
            do_ra(stack_a, operations);
            count_high++;
        }
    }
    t = count_high;
    while (t--)
    {
        do_rra(stack_a, operations);
    }
    td_quicksort(stack_a, stack_b, count_high, operations);
    
    t = count_mid;
    while (t--)
    {
        do_pa(stack_a, stack_b, operations);
    }
    td_quicksort(stack_a, stack_b, count_mid, operations);

    t = count_low;
    while (t--)
    {
        do_rrb(stack_b, operations);
        do_pa(stack_a, stack_b, operations);
    }
    td_quicksort(stack_a, stack_b, count_low, operations);
    
}

void test_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    td_quicksort(stack_a, stack_b, stack_a->size, operations);
}
