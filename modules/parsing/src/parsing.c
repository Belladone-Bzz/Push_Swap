#include "push_swap.h"

t_error_flag	parsing(int argc, char *argv[], t_parsed_data *parsed_data)
{
	t_error_flag	error_flag;

	parsed_data->algo_flag = UNSET;
	parsed_data->bench_flag = FALSE;
	parsed_data->stack_a.head = NULL;
	parsed_data->stack_a.tail = NULL;
	parsed_data->stack_a.list_size = 0;
	parsed_data->disorder = 0;
	error_flag = get_flags(&argc, &argv, parsed_data);
	if (!argc)
		error_flag = MISSING_ARG_ERR;
	if (error_flag == NO_ERR)
		error_flag = compute_values(argc, argv, parsed_data);
	if (error_flag != NO_ERR)
		free_stack(&(parsed_data->stack_a.head));
	return (error_flag);
}
