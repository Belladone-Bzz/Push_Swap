#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include "../modules/parsing/include/parsing.h"
# include "../modules/operations/include/operations.h"
# include "../modules/algorithms/include/algorithms.h"

typedef enum e_algo_flag
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE,
	UNSET,
}	t_algo_flag;

typedef enum e_bool_flag
{
	FALSE,
	TRUE,
}	t_bool_flag;

typedef enum e_operations
{
	SWAP_A,			// 0
	ROTATE_A,		// 1
	R_ROTATE_A,		// 2
	SWAP_B,			// 3
	ROTATE_B,		// 4
	R_ROTATE_B,		// 5
	SWAP_S,			// 6
	ROTATE_S,		// 7
	R_ROTATE_S,		// 8
	PUSH_A,			// 9
	PUSH_B,			// 10
	NO_PRINT,		// 11
}	t_operations;

typedef enum e_error_flag
{
	NO_ERR,
	MALLOC_ERR,
	MISSING_ARG_ERR,
	VALUE_ARG_ERR,
	DUP_FLAG_ERR,
	DUP_VALUE_ERR,
	ILLEGAL_VALUE_ERR,
	ALGORITHM_ERR,
	OPERATION_ERR,
}	t_error_flag;

typedef struct s_value_node
{
	struct s_value_node	*next;
	struct s_value_node	*prev;
	ssize_t				value;
}						t_node;

typedef struct s_stack_info
{
	t_node	*head;
	t_node	*tail;
	size_t	list_size;
}			t_stack_info;

typedef struct s_parsed_data // returned by parsing function
{
	t_algo_flag		algo_flag;
	t_bool_flag		bench_flag;
	t_stack_info	stack_a;
	size_t			disorder;
}					t_parsed_data;

typedef struct s_push_swap_data // returned by push_swap function
{
	t_stack_info	stack_a;
	t_stack_info	stack_b;
	size_t			number_of_operations;
	size_t			operations_used[11];
}					t_push_swap_data;

t_error_flag	push_swap(t_parsed_data parsed_data);
void			free_stack(t_node **value_list);

#endif
