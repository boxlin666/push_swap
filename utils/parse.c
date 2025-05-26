/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:13:37 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 15:30:51 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>

void push_to_stack(t_stack *stack, int value)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        error_exit();
    new_node->value = value;
    new_node->next = NULL; // 新节点将是栈底，next 为空
    new_node->prev = stack->tail; // 连接到之前的栈底
    if (stack->tail)
        stack->tail->next = new_node; // 更新之前的栈底的 next 指针
    else
        stack->head = new_node; // 如果栈为空，head 指向新节点
    stack->tail = new_node; // 更新栈底为新节点
    stack->size++;
}

int is_valid_number(const char *str, long *result)
{
    int i = 0;
    int sign = 1;
    *result = 0;

    if (!str || str[0] == '\0')
        return 0;
    if (str[0] == '-' || str[0] == '+')
    {
        if (str[0] == '-')
            sign = -1;
        i++;
    }
    if (str[i] == '\0')
        return 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        *result = *result * 10 + (str[i] - '0');
        if (*result * sign > INT_MAX || *result * sign < INT_MIN)
            return 0;
        i++;
    }
    *result *= sign;
    return 1;
}

int has_duplicates(t_stack *stack)
{
    t_node *current = stack->head;
    while (current)
    {
        t_node *next = current->next;
        while (next)
        {
            if (current->value == next->value)
                return 1;
            next = next->next;
        }
        current = current->next;
    }
    return 0;
}

void free_split(char **numbers)
{
    int i = 0;
    if (!numbers)
        return;
    while (numbers[i])
    {
        free(numbers[i]);
        i++;
    }
    free(numbers);
}

char **split_input(const char *str)
{
    int count = 0;
    int i = 0;
    char *tmp = strdup(str);
    if (!tmp)
        return NULL;
    char *token = strtok(tmp, " ");
    while (token)
    {
        count++;
        token = strtok(NULL, " ");
    }
    free(tmp);
    char **numbers = malloc(sizeof(char *) * (count + 1));
    if (!numbers)
        return NULL;
    tmp = strdup(str);
    if (!tmp)
    {
        free(numbers);
        return NULL;
    }
    token = strtok(tmp, " ");
    while (token)
    {
        numbers[i] = strdup(token);
        if (!numbers[i])
        {
            free_split(numbers);
            free(tmp);
            return NULL;
        }
        i++;
        token = strtok(NULL, " ");
    }
    numbers[i] = NULL;
    free(tmp);
    return numbers;
}



int parse_input(t_stack *stack_a, int argc, char **argv)
{
    int i;
    long num;
    char **numbers;

    if (argc < 2)
        return 0;
    i = 1;
    if (argc == 2)
    {
        numbers = split_input(argv[1]);
        if (!numbers)
            error_exit();
        i = 0;
        while (numbers[i])
        {
            if (!is_valid_number(numbers[i], &num))
            {
                free_split(numbers);
                error_exit();
            }
            if (num < INT_MIN || num > INT_MAX)
            {
                free_split(numbers);
                error_exit();
            }
            push_to_stack(stack_a, (int)num);
            i++;
        }
        free_split(numbers);
    }
    else
    {
        while (i < argc)
        {
            if (!is_valid_number(argv[i], &num))
                error_exit();
            if (num < INT_MIN || num > INT_MAX)
                error_exit();
            push_to_stack(stack_a, (int)num);
            i++;
        }
    }
    if (has_duplicates(stack_a))
        error_exit();
    return 1;
}