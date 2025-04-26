/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:21:51 by helin             #+#    #+#             */
/*   Updated: 2025/04/26 16:42:54 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// 交换两个整数的函数
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fisher-Yates 洗牌算法
void shuffle(int *array, int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // 随机生成 [0, i]
        swap(&array[i], &array[j]);
    }
}

// 初始化栈并填充随机排列的数值
t_stack *init_test_stack(int size) {
    t_stack *stack = malloc(sizeof(t_stack));
    if (!stack) return NULL;  // 检查 malloc 是否成功

    // 创建数组来存储 0 到 size-1 的数值
    int *values = malloc(sizeof(int) * size);
    if (!values) {
        free(stack);
        return NULL;  // 如果分配失败，清理并返回 NULL
    }

    // 填充数组 [0, 1, 2, ..., size-1]
    for (int i = 0; i < size; i++) {
        values[i] = i;
    }

    // 打乱数组
    shuffle(values, size);

    // 使用打乱后的数组来创建节点
    t_node *first = malloc(sizeof(t_node));
    if (!first) {
        free(values);
        free(stack);
        return NULL;  // 检查 malloc 是否成功
    }
    first->value = values[0];
    t_node *current = first;

    for (int i = 1; i < size; i++) {
        t_node *new_node = malloc(sizeof(t_node));
        if (!new_node) {
            // 清理之前分配的内存
            free(values);
            free(stack);
            return NULL;
        }
        new_node->value = values[i];
        current->next = new_node;
        current = new_node;
    }

    current->next = NULL;  // 最后一个节点的 next 设置为 NULL
    stack->top = first;
    stack->size = size;

    // 清理临时数组
    free(values);

    return stack;
}

t_stack *init_empty_stack(void)
{
    t_stack *stack;

    stack = (t_stack *)malloc(sizeof(t_stack));
    if (!stack)
        return (NULL);  // 内存分配失败，返回NULL
    stack->top = NULL;  // 空栈，top指针设为NULL
    stack->size = 0;    // 空栈，size设为0
    return (stack);
}

void    print_stack(t_stack *a)
{
    t_node *curr = a->top;
    while (curr)
    {
        printf("%d\n", curr->value);
        curr = curr->next;
    }
}
