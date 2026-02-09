#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "push_swap.h"

typedef enum e_error_flag		t_error_flag;
typedef enum e_operations		t_operations;
typedef struct s_value_node		t_node;
typedef struct s_stack_info		t_stack_info;
typedef struct s_push_swap_data	t_push_swap_data;

size_t			is_stack_ordered(t_node *head);
size_t			find_maximal_value(t_stack_info stack);
size_t			find_minimal_value(t_stack_info stack);
void			push_value_to_a(t_push_swap_data *ps_data, size_t pos);
void			push_value_to_b(t_push_swap_data *ps_data, size_t pos);
void			sort_three(t_push_swap_data *ps_data, size_t pos);

t_error_flag	create_sorted_tab(ssize_t **sorted_values, t_stack_info stack);
void			swap_values(ssize_t *ptr1, ssize_t *ptr2);

t_error_flag	simple_algo(t_push_swap_data *ps_data);
t_error_flag	medium_algo(t_push_swap_data *ps_data);
t_error_flag	complex_algo(t_push_swap_data *ps_data);

#endif
