#include "push_swap.h"

static size_t	get_max_bits(size_t list_size)
{
	size_t	bits_count;

	bits_count = 0;
	while (list_size > 0)
	{
		list_size /= 2;
		bits_count++;
	}
	return (bits_count);
}

static size_t	get_index(ssize_t *sorted_values, size_t array_size,
	t_stack_info stack)
{
	size_t	index;

	index = 0;
	while (index < array_size + 1)
	{
		if (sorted_values[index] == stack.head->value)
			return (index);
		index++;
	}
	return (0);
}

static void	browse_bits(ssize_t *sorted_values, size_t max_index,
				t_push_swap_data *ps_data)
{
	size_t	bit;
	size_t	max_bits;
	size_t	index;
	size_t	list_size;

	max_bits = get_max_bits(max_index);
	bit = 0;
	while (bit < max_bits && is_stack_ordered(ps_data->stack_a.head) == 0)
	{
		list_size = ps_data->stack_a.list_size;
		index = 0;
		while (index < list_size)
		{
			if ((get_index(sorted_values, max_index,
						ps_data->stack_a) >> bit) & 1)
				call_operation(ROTATE_A, ps_data);
			else
				call_operation(PUSH_B, ps_data);
			index++;
		}
		while (ps_data->stack_b.list_size > 0)
			call_operation(PUSH_A, ps_data);
		bit++;
	}
}

t_error_flag	complex_algo(t_push_swap_data *ps_data)
{
	ssize_t	*sorted_values;
	size_t	max_index;

	if (create_sorted_tab(&sorted_values, ps_data->stack_a) == MALLOC_ERR)
		return (MALLOC_ERR);
	max_index = ps_data->stack_a.list_size - 1;
	browse_bits(sorted_values, max_index, ps_data);
	free(sorted_values);
	return (NO_ERR);
}
