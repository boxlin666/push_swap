#include "stack.h"
#include <unistd.h>

void    sa(t_stack *a);
void    ra(t_stack *a);
void    rra(t_stack *a);

void small_sort(t_stack *a)
{
    int first = a->top->value;
    int second = a->top->next->value;
    int third = a->top->next->next->value;

    if (first > second && second < third && first < third)
        sa(a);         // 2 1 3
    else if (first > second && second > third)
    {
        sa(a);
        rra(a);        // 3 2 1
    }
    else if (first > second && second < third && first > third)
        ra(a);         // 3 1 2
    else if (first < second && second > third && first < third)
    {
        sa(a);
        ra(a);         // 1 3 2
    }
    else if (first < second && second > third && first > third)
        rra(a);        // 2 3 1
}
