/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/08 16:31:03 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdlib.h>
#include <limits.h>

int get_chunk_count(int size)
{
    if (size <= 100)
        return 5;
    else
        return size / 50 + 5;
}

int find_ra_next(t_stack *stack, int min_val, int max_val)
{
    if (stack->size == 0)
        return 0;
    t_node *current = stack->head;
    int step = 0;
    while (current)
    {
        if (current->value >= min_val && current->value < max_val)
            return step;
        current = current->next;
        step++;
    }
    return stack->size;
}

int find_rra_next(t_stack *stack, int min_val, int max_val)
{
    if (stack->size == 0)
        return 0;
    t_node *current = stack->tail;
    int step = 1;
    while (current)
    {
        if (current->value >= min_val && current->value < max_val)
            return step;
        current = current->prev;
        step--;
    }
    return stack->size;
}

void slice_stack(t_stack *stack_a, t_stack *stack_b, t_operation **operations, int min_val, int max_val)
{
    int size = max_val - min_val;
    int forward_steps;
    int backward_steps;

    while (size)
    {
        forward_steps = find_ra_next(stack_a, min_val, max_val);
        backward_steps = find_rra_next(stack_a, min_val, max_val);
        if (forward_steps <= backward_steps)
            while (forward_steps--)
                do_ra(stack_a, operations);
        else
            while (backward_steps--)
                do_rra(stack_a, operations);
        do_pb(stack_a, stack_b, operations);
        if (stack_b->head->value < (min_val + max_val) / 2)
            do_rb(stack_b, operations);
        size--;
    }
}

int max(int a, int b)
{
    if(a >= b)
        return a;
    return b;
}

int get_val_of_idx(t_stack *stack, int index)
{
    t_node *current = stack->head;
    int step=0;
    while(step++)
    {
        if(step == index)
            return current->value;
        current = current->next;
    }
    return 0;
}
int get_target_index(t_stack *stack_a, int value)
{
    if (stack_a->size == 0)
        return 0;

    int min_val = __INT_MAX__;
    int max_val = -__INT_MAX__;

    // 先找出最小值和最大值（用于环形插入）
    t_node *tmp = stack_a->head;
    while (tmp)
    {
        if (tmp->value < min_val)
            min_val = tmp->value;
        if (tmp->value > max_val)
            max_val = tmp->value;
        tmp = tmp->next;
    }

    // 如果 value 是比最小还小或比最大还大，应该插入在最小值之前
    if (value < min_val || value > max_val)
    {
        t_node *node = stack_a->head;
        int i = 0;
        while (node)
        {
            if (node->value == min_val)
                return i;
            node = node->next;
            i++;
        }
    }

    // 否则在中间插入，找第一个满足 current < value < next 的位置
    t_node *node = stack_a->head;
    t_node *next = node->next;
    int i = 1;
    while (next)
    {
        if (node->value < value && value < next->value)
            return i;
        node = next;
        next = next->next;
        i++;
    }

    return 0;
}

t_rotation_plan compute_rotation_plan(int a_idx, int b_idx, int size_a, int size_b, int a_val, int b_val) {
    t_rotation_plan best = {0};

    int ra = a_idx;
    int rra = size_a - a_idx;
    int rb = b_idx;
    int rrb = size_b - b_idx;

    int plans[4];
    plans[0] = max(ra, rb);            // 同时正转 → rr
    plans[1] = max(rra, rrb);          // 同时反转 → rrr
    plans[2] = ra + rrb;               // A正转，B反转
    plans[3] = rra + rb;               // A反转，B正转

    int min = plans[0];
    int strat = 0;
    for (int i = 0; i < 4; i++) {
        if (plans[i] < min) {
            min = plans[i];
            strat = i;
        }
    }

    best.a_idx = a_idx;
    best.b_idx = b_idx;
    best.ra = ra;
    best.rra = rra;
    best.rb = rb;
    best.rrb = rrb;
    best.total = min + 2 * max(a_val, b_val) - a_val - b_val;
    best.strategy = strat;

    return best;
}

void execute_plan(t_stack *stack_a, t_stack *stack_b, t_operation **operations, t_rotation_plan best_plan)
{
    if(best_plan.strategy == 0)
    {
        while (best_plan.ra>0)
        {
            do_ra(stack_a, operations);
            best_plan.ra--;
        }
        while (best_plan.rb>0)
        {
            do_rb(stack_b, operations);
            best_plan.rb--;
        }      
    }
    else if(best_plan.strategy == 1)
    {
        while (best_plan.rra>0)
        {
            do_rra(stack_a, operations);
            best_plan.rra--;
        }
        while (best_plan.rrb>0)
        {
            do_rrb(stack_b, operations);
            best_plan.rrb--;
        } 
    }
    else if(best_plan.strategy == 2)
    {
        while (best_plan.ra>0)
        {
            do_ra(stack_a, operations);
            best_plan.ra--;
        }
        while (best_plan.rrb>0)
        {
            do_rrb(stack_b, operations);
            best_plan.rrb--;
        }
    }
    else if(best_plan.strategy == 3)
    {
        while (best_plan.rra>0)
        {
            do_rra(stack_a, operations);
            best_plan.rra--;
        }
        while (best_plan.rb>0)
        {
            do_rb(stack_b, operations);
            best_plan.rb--;
        }
    }
}
void move_next_element_to_b(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    t_node *current = stack_a->head;
    int a_idx=0, b_idx;
    t_rotation_plan current_plan;
    t_rotation_plan best_plan;
    int b_val;
    while (current)
    {
        b_idx = get_target_index(stack_b, current->value);
        b_val = get_val_of_idx(stack_b, a_idx);
        current_plan = compute_rotation_plan(a_idx, b_idx, stack_a->size, stack_b->size, current->value, b_val);
        if(a_idx==0 || current_plan.total < best_plan.total)
            best_plan = current_plan;
        current = current->next;
        a_idx++;
    }
    // print_rotation_plan(best_plan);
    execute_plan(stack_a, stack_b, operations, best_plan);
    do_pb(stack_a, stack_b, operations);
}

void move_next_element_to_a(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    t_node *current = stack_b->head;
    int a_idx, b_idx=0;
    t_rotation_plan current_plan;
    t_rotation_plan best_plan;
    int a_val;
    while (current)
    {
        a_idx = get_target_index(stack_a, current->value);
        a_val = get_val_of_idx(stack_a, a_idx);
        current_plan = compute_rotation_plan(a_idx, b_idx, stack_a->size, stack_b->size, a_val, current->value);
        if(b_idx==0 || current_plan.total < best_plan.total)
            best_plan = current_plan;
        current = current->next;
        b_idx++;
    }
    // print_rotation_plan(best_plan);
    execute_plan(stack_a, stack_b, operations, best_plan);
    do_pa(stack_a, stack_b, operations);
}

void sort_small_inverse(t_stack *stack, t_operation **operations)
{
    if (stack->size == 2)
    {
        if (stack->head->value < stack->head->next->value)
            do_sa(stack, operations);
    }
    else if (stack->size == 3)
    {
        int a = stack->head->value;
        int b = stack->head->next->value;
        int c = stack->head->next->next->value;
        if (a > b && b < c && a < c) // 2,1,3
            do_rrb(stack, operations);
        else if (a > b && b > c && a > c) // 3,2,1
        {
            ;
        }
        else if (a < b && b > c && a > c) // 2,3,1
        {
            do_sb(stack, operations);
        }
        else if (a < b && b > c && a < c) // 1,3,2
        {
            do_rb(stack, operations);
        }
        else if (a > b && b < c && a > c) // 3,1,2
        {
            do_rrb(stack, operations);
            do_sb(stack, operations);
        }
    }
}

void test_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    while(stack_b->size < 3)
    {
        do_pb(stack_a, stack_b, operations);
    }
    sort_small_inverse(stack_b, operations);
    print_stacks(stack_a, stack_b);
    while(stack_a->size > 3)
    {
        move_next_element_to_b(stack_a, stack_b, operations);
    }
    sort_small(stack_a, operations);
    while(stack_b->size > 0)
    {
        move_next_element_to_a(stack_a, stack_b, operations);
    }
    int ra_step = stack_a ->size - stack_a->head->value;
    int rra_step = stack_a ->head ->value;
    if(ra_step <= rra_step)
    {
        while (ra_step--)
        {
            do_ra(stack_a, operations);
        }
    }
    else
    {
        while (rra_step--)
        {
            do_rra(stack_a, operations);
        }
        
    }
}
