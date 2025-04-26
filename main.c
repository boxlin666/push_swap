#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void small_sort(t_stack *a);
void small_sort_5(t_stack *a, t_stack *b);
t_stack *init_test_stack(int size);
t_stack *init_empty_stack();
void    print_stack(t_stack *a);

int main(void)
{
    int size = 5;
    t_stack *a = init_test_stack(size);
    t_stack *b = init_empty_stack();

    printf("Before sorting:\n");
    print_stack(a);

    if(size == 3)
        small_sort(a);
    else if (size == 5)
        small_sort_5(a, b);

    printf("After sorting:\n");
    print_stack(a);

    return (0);
}
