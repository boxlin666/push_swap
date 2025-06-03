/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:53:51 by helin             #+#    #+#             */
/*   Updated: 2025/06/03 12:05:32 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"push_swap.h"

int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;
    t_operation *operations;

    stack_a = init_stack();
    stack_b = init_stack();
    operations = NULL;
    if (!stack_a || !stack_b)
    {
        free_stack(stack_a);
        free_stack(stack_b);
        error_exit();
    }
    if (parse_input(stack_a, argc, argv)) // 解析输入，有参数返回 1
    {
        normalize_stack(stack_a);
        push_swap(stack_a, stack_b, &operations); // 调用排序函数
        // print_stacks(stack_a, stack_b);
        optimize_operations(operations);
        operations = compress_operations(operations);
        print_operations(operations); // 输出操作序列
        free_operations(operations); // 释放操作序列内存
    }
    free_stack(stack_a); // 释放栈内存
    free_stack(stack_b);
    return (0);
}
