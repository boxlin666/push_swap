/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:37:44 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 16:36:31 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>

typedef struct s_pair
{
	int					a;
	int					b;
}						t_pair;

typedef struct s_node
{
	int					value;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_stack
{
	t_node				*head;
	t_node				*tail;
	int					size;
}						t_stack;

typedef struct s_operation
{
	char				*op;
	struct s_operation	*next;
}						t_operation;

typedef struct s_context
{
	t_stack				*stack_a;
	t_stack				*stack_b;
	t_operation			*operations;
}						t_context;

typedef struct s_rotation_plan
{
	int					a_idx;
	int					b_idx;
	int					ra;
	int					rra;
	int					rb;
	int					rrb;
	int					total;
	int					strategy;
}						t_rotation_plan;

t_stack					*init_stack(void);
void					push_swap(t_context *ctx);
int						parse_input(t_context *ctx, int argc, char **argv);
void					quick_sort(int *arr, int low, int high);
void					normalize_stack(t_stack *a);

void					print_stacks(t_stack *stack_a, t_stack *stack_b);
void					print_rotation_plan(t_rotation_plan plan);

void					do_sa(t_context *ctx);
void					do_sb(t_context *ctx);
void					do_pa(t_context *ctx);
void					do_pb(t_context *ctx);
void					do_ra(t_context *ctx);
void					do_rb(t_context *ctx);
void					do_rra(t_context *ctx);
void					do_rrb(t_context *ctx);
void					do_ss(t_context *ctx);
void					do_rr(t_context *ctx);
void					do_rrr(t_context *ctx);

void					sort_small(t_context *ctx);
void					sort_medium(t_context *ctx);

void					slice_stack(t_context *ctx, int min_val, int max_val);
t_rotation_plan			compute_rotation_plan(t_pair idx, t_pair size,
							int a_val, int b_val);
void					execute_rotation_plan(t_context *ctx,
							t_rotation_plan plan);
int						get_target_index(t_stack *stack_a, int value);
void					move_next_element(t_context *ctx);

void					sort_large(t_context *ctx);
t_operation				*add_operation(t_operation *head, const char *op);
void					append_op(t_operation **head, t_operation **tail,
							const char *op);
t_operation				*optimize_operations(t_operation *head);
t_operation				*compress_operations(t_operation *head,
							t_rotation_plan rp);
void					free_operations(t_operation *operations);
void					print_operations(t_operation *operations);
void					error_exit(t_context *ctx);
void					free_stack(t_stack *stack);
void					free_split(char **numbers);
int						ft_max(int a, int b);
int						ft_min(int a, int b);
#endif