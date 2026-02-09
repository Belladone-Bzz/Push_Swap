#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "../../../include/push_swap.h"

typedef enum e_error_flag		t_error_flag;
typedef enum e_operations		t_operations;
typedef struct s_value_node		t_node;
typedef struct s_push_swap_data	t_push_swap_data;

/*
The call_operation is the only exposed function here, responsible of calling 
the right operation and giving it the right stack to work on. This lies on an 
operation flag received as argument, with different operations distributed in 
a particular order : SWAP, ROTATE, R_ROTATE and PUSH in its own condition. 
If no error is returned, call_operation adds 1 to the according push_swap_data 
counters, and returns NO_ERR. Each operation function must : check that the 
operation is physically possible, otherwise do nothing, apply all needed 
changes on the provided stack_info structure and print the right flag of 
operation.

Returned values : NO_ERR, OPERATION_ERR (wrong operation flag input)
*/
t_error_flag	call_operation(t_operations op_flag,
					t_push_swap_data *ps_data);

#endif