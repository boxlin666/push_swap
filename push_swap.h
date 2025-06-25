/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:37:44 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 11:32:18 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
#include <stddef.h>

typedef struct s_node
{
    int value;           // 原始归一化后的数字（0..n-1）
    int in_lis;          // 0 表示不在 LIS，1 表示在 LIS
    struct s_node *next; // 指向下一个节点
    struct s_node *prev; // 指向前一个节点
} t_node;

typedef struct s_stack
{
    t_node *head; // 栈顶（头部）
    t_node *tail; // 栈底（尾部）
    int size;     // 栈大小
} t_stack;

typedef struct s_operation
{
    char *op;                 // 操作字符串，如 "sa", "pb"
    struct s_operation *next; // 下一个操作
} t_operation;

typedef struct s_rotation_plan{
    int a_idx;
    int b_idx;
    int ra;  // 正转A次数
    int rra; // 反转A次数
    int rb;  // 正转B次数
    int rrb; // 反转B次数
    int total; // 总操作数
    int strategy; // 0:ra+rb, 1:rra+rrb, 2:ra+rrb, 3:rra+rb
} t_rotation_plan;

t_stack *init_stack(void);
void push_swap(t_stack *stack_a, t_stack *stack_b, t_operation **operations);
int parse_input(t_stack *stack_a, int argc, char **argv);
void quick_sort(int *arr, int low, int high);
void normalize_stack(t_stack *a);
void mark_LIS(t_stack *stack_a);

void print_stacks(t_stack *stack_a, t_stack *stack_b);
void print_rotation_plan(t_rotation_plan plan);

void do_sa(t_stack *stack_a, t_operation **operations);
void do_sb(t_stack *stack_b, t_operation **operations);
void do_pa(t_stack *stack_a, t_stack *stack_b, t_operation **operations);
void do_pb(t_stack *stack_a, t_stack *stack_b, t_operation **operations);
void do_ra(t_stack *stack_a, t_operation **operations);
void do_rb(t_stack *stack_b, t_operation **operations);
void do_rra(t_stack *stack_a, t_operation **operations);
void do_rrb(t_stack *stack_b, t_operation **operations);
void do_ss(t_stack *stack_a, t_stack *stack_b, t_operation **operations);
void do_rr(t_stack *stack_a, t_stack *stack_b, t_operation **operations);
void do_rrr(t_stack *stack_a, t_stack *stack_b, t_operation **operations);

void sort_small(t_stack *stack_a, t_operation **operations);
void sort_medium(t_stack *stack_a, t_stack *stack_b, t_operation **operations);
void sort_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations);
t_operation *add_operation(t_operation *head, const char *op);
t_operation *optimize_operations(t_operation *head);
t_operation *compress_operations(t_operation *head);
void print_operations(t_operation *operations);
void free_operations(t_operation *operations);

void error_exit(void);
void free_stack(t_stack *stack);

#endif