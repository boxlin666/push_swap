/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:54:53 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 15:26:45 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

t_operation *add_operation(t_operation *head, const char *op)
{
    t_operation *new_op = malloc(sizeof(t_operation));
    // if (!new_op)
    //     error_exit();

    new_op->op = strdup(op);
    // if (!new_op->op)
    // {
    //     free(new_op);
    //     error_exit();
    // }

    new_op->next = NULL;

    if (!head)
        return new_op;

    t_operation *tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_op;

    return head;
}

void print_operations(t_operation *operations)
{
    t_operation *tmp;

    tmp = operations->next;
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

t_operation *new_op(const char *op_str) {
    t_operation *op = malloc(sizeof(t_operation));
    if (!op) return NULL;
    op->op = strdup(op_str);
    op->next = NULL;
    return op;
}

// 添加操作到链表末尾
void append_op(t_operation **head, t_operation **tail, const char *op_str) {
    t_operation *new = new_op(op_str);
    if (!new) return;
    if (!*head)
        *head = *tail = new;
    else {
        (*tail)->next = new;
        *tail = new;
    }
}

// 主优化函数
t_operation *compress_operations(t_operation *head)
{
    t_operation *new_head = NULL;
    t_operation *new_tail = NULL;
    t_operation *current = head;

    while (current)
    {
        // 检查是否是旋转操作
        if (strcmp(current->op, "ra") == 0 || strcmp(current->op, "rb") == 0 ||
            strcmp(current->op, "rra") == 0 || strcmp(current->op, "rrb") == 0)
        {
            int ra = 0, rb = 0, rra = 0, rrb = 0;

            // 处理连续的旋转操作，直到遇到非旋转操作
            while (current && (strcmp(current->op, "ra") == 0 || strcmp(current->op, "rb") == 0 ||
                               strcmp(current->op, "rra") == 0 || strcmp(current->op, "rrb") == 0))
            {
                if (strcmp(current->op, "ra") == 0) ra++;
                else if (strcmp(current->op, "rb") == 0) rb++;
                else if (strcmp(current->op, "rra") == 0) rra++;
                else if (strcmp(current->op, "rrb") == 0) rrb++;

                t_operation *tmp = current;
                current = current->next;
                free(tmp->op);
                free(tmp);
            }

            // 合并正转
            int rr = (ra < rb) ? ra : rb;
            ra -= rr;
            rb -= rr;
            for (int i = 0; i < rr; i++) append_op(&new_head, &new_tail, "rr");
            for (int i = 0; i < ra; i++) append_op(&new_head, &new_tail, "ra");
            for (int i = 0; i < rb; i++) append_op(&new_head, &new_tail, "rb");

            // 合并逆转
            int rrr = (rra < rrb) ? rra : rrb;
            rra -= rrr;
            rrb -= rrr;
            for (int i = 0; i < rrr; i++) append_op(&new_head, &new_tail, "rrr");
            for (int i = 0; i < rra; i++) append_op(&new_head, &new_tail, "rra");
            for (int i = 0; i < rrb; i++) append_op(&new_head, &new_tail, "rrb");
        }
        else
        {
            // 非旋转类操作，直接复制
            append_op(&new_head, &new_tail, current->op);
            t_operation *tmp = current;
            current = current->next;
            free(tmp->op);
            free(tmp);
        }
    }

    return new_head;
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