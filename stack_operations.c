/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:12:25 by helin             #+#    #+#             */
/*   Updated: 2025/04/26 17:29:33 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include <unistd.h>

void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

void sa(t_stack *a) {
    if (a->top && a->top->next) {
        t_node *first = a->top;
        t_node *second = first->next;

        first->next = second->next;
        second->next = first;
        a->top = second;
    }
}

void sb(t_stack *b) {
    if (b->top && b->top->next) {
        t_node *first = b->top;
        t_node *second = first->next;

        first->next = second->next;
        second->next = first;
        b->top = second;
    }
}

void ss(t_stack *a, t_stack *b) {
    sa(a);
    sb(b);
}

void pa(t_stack *a, t_stack *b) {
    if (b->top) {
        t_node *temp = b->top;
        b->top = b->top->next;
        temp->next = a->top;
        a->top = temp;
        a->size++;
        b->size--;
    }
}

void pb(t_stack *a, t_stack *b)
{
    if (a->top) {
        t_node *temp = a->top;
        a->top = a->top->next;
        temp->next = b->top;
        b->top = temp;
        a->size--;
        b->size++;    
    }

}


void ra(t_stack *a) {
    if (a->top && a->top->next) {
        t_node *first = a->top;
        a->top = first->next;
        first->next = NULL;

        t_node *current = a->top;
        while (current->next) {
            current = current->next;
        }
        current->next = first;
    }
}

void rb(t_stack *b) {
    if (b->top && b->top->next) {
        t_node *first = b->top;
        b->top = first->next;
        first->next = NULL;

        t_node *current = b->top;
        while (current->next) {
            current = current->next;
        }
        current->next = first;
    }
}

void rr(t_stack *a, t_stack *b) {
    ra(a);
    rb(b);
}

void rra(t_stack *a) {
    if (a->top && a->top->next) {
        t_node *current = a->top;
        while (current->next->next) {
            current = current->next;
        }

        t_node *last = current->next;
        current->next = NULL;
        last->next = a->top;
        a->top = last;
    }
}

void rrb(t_stack *b) {
    if (b->top && b->top->next) {
        t_node *current = b->top;
        while (current->next->next) {
            current = current->next;
        }

        t_node *last = current->next;
        current->next = NULL;
        last->next = b->top;
        b->top = last;
    }
}

void rrr(t_stack *a, t_stack *b) {
    rra(a);
    rrb(b);
}
