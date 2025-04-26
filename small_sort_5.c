#include "stack.h"
#include <unistd.h>

void	sa(t_stack *a);
void	sb(t_stack *b);
void	ra(t_stack *a);
void	rra(t_stack *a);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

#include "stack.h"
#include <limits.h>

void sa(t_stack *a);
void sb(t_stack *b);
void ra(t_stack *a);
void rra(t_stack *a);
void pa(t_stack *a, t_stack *b);
void pb(t_stack *a, t_stack *b);

// 查找最小值并记录其位置
int find_min_and_position(t_stack *a, int *position)
{
    t_node *current;
    int min, pos, i;

    if (!a || !a->top)
    {
        *position = -1;
        return (INT_MAX);
    }
    current = a->top;
    min = current->value;
    pos = 0;
    i = 0;
    while (current)
    {
        if (current->value < min)
        {
            min = current->value;
            pos = i;
        }
        current = current->next;
        i++;
    }
    *position = pos;
    return (min);
}

// 用于处理 3 个元素的排序
int small_sort_3(t_stack *a)
{
    int top, mid, bottom;

    if (!a || !a->top || !a->top->next || !a->top->next->next || a->size != 3)
        return (0);
    top = a->top->value;
    mid = a->top->next->value;
    bottom = a->top->next->next->value;
    if (top > mid && mid < bottom && top < bottom) // 2 1 3 -> 1 2 3
        sa(a);
    else if (top > mid && mid > bottom) // 3 2 1 -> 2 3 1 -> 1 2 3
    {
        sa(a);
        rra(a);
    }
    else if (top > mid && mid < bottom && top > bottom) // 3 1 2 -> 1 3 2
        ra(a);
    else if (top < mid && mid > bottom && top < bottom) // 1 3 2 -> 3 1 2 -> 1 2 3
    {
        sa(a);
        ra(a);
    }
    else if (top < mid && mid > bottom && top > bottom) // 2 3 1 -> 1 2 3
        rra(a);
    return (1);
}

// 主函数：处理 5 个元素的排序
int small_sort_5(t_stack *a, t_stack *b)
{
    int min, pos;

    if (!a || !b || a->size != 5)
        return (0);
    // 将 2 个最小元素推到栈 b
    while (a->size > 3)
    {
        min = find_min_and_position(a, &pos);
        if(min == -1)
            return -1;
        if (pos == -1)
            return (0);
        if (pos == 0)
            pb(b, a);
        else if (pos == 1)
        {
            sa(a);
            pb(b, a);
        }
        else if (pos <= a->size / 2)
        {
            while (pos--)
                ra(a);
            pb(b, a);
        }
        else
        {
            while (a->size - pos++)
                rra(a);
            pb(b, a);
        }
    }
    // 排序栈 a 的 3 个元素
    if (!small_sort_3(a))
        return (0);
    // 确保栈 b 的元素按降序排列（顶部较大）
    if (b->size == 2 && b->top->value < b->top->next->value)
        sb(b);
    // 将栈 b 的元素推回栈 a
    while (b->top)
        pa(a, b);
    return (1);
}