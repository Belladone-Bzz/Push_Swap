#include "push_swap.h"

void	sort_three(t_push_swap_data *ps_data, size_t pos)
{
	if (pos == 0)
	{
		call_operation(ROTATE_A, ps_data);
		call_operation(SWAP_A, ps_data);
		call_operation(R_ROTATE_A, ps_data);
	}
	else if (pos == 2)
	{
		if (ps_data->stack_a.head->value
			> ps_data->stack_a.head->next->value)
		{
			call_operation(SWAP_A, ps_data);
			call_operation(R_ROTATE_A, ps_data);
		}
		else
			call_operation(R_ROTATE_A, ps_data);
	}
	else if (pos == 1)
	{
		if (ps_data->stack_a.head->value
			> ps_data->stack_a.head->next->next->value)
			call_operation(ROTATE_A, ps_data);
		else
			call_operation(SWAP_A, ps_data);
	}
}

t_error_flag	simple_algo(t_push_swap_data *ps_data)
{
	while (is_stack_ordered(ps_data->stack_a.head) == 0
		&& ps_data->stack_a.list_size > 3)
	{
		push_value_to_b(ps_data, find_minimal_value(ps_data->stack_a));
	}
	if (ps_data->stack_a.list_size == 3
		&& is_stack_ordered(ps_data->stack_a.head) == 0)
		sort_three(ps_data, find_minimal_value(ps_data->stack_a));
	else if (ps_data->stack_a.list_size == 2
		&& find_minimal_value(ps_data->stack_a) == 1)
		call_operation(SWAP_A, ps_data);
	while (ps_data->stack_b.head != NULL)
		call_operation(PUSH_A, ps_data);
	return (NO_ERR);
}
