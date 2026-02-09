#include "push_swap.h"

static size_t	ft_square_root(size_t value)
{
	size_t	sq_root;

	sq_root = 3;
	while (sq_root * sq_root < value)
		sq_root++;
	return (sq_root);
}

static size_t	check_closest_value(t_stack_info stack_a,
					ssize_t *sorted_values, size_t chunk_amount,
					size_t value_index)
{
	t_node	*temp_head;
	t_node	*temp_tail;
	size_t	index;

	temp_head = stack_a.head;
	temp_tail = stack_a.tail;
	while (temp_head != NULL && temp_tail != NULL)
	{
		index = value_index;
		while (index < chunk_amount && index < stack_a.list_size)
		{
			if (sorted_values[index] == temp_head->value
				||sorted_values[index] == temp_tail->value)
				return (index);
			index++;
		}
		temp_head = temp_head->next;
		temp_tail = temp_tail->prev;
	}
	return (value_index);
}

static size_t	find_value_position(t_stack_info stack_a, ssize_t value)
{
	t_node	*temp;
	size_t	pos;

	temp = stack_a.head;
	pos = 0;
	while (temp != NULL && temp->value != value)
	{
		temp = temp->next;
		pos++;
	}
	return (pos);
}

static void	browse_array(t_push_swap_data *ps_data, ssize_t	*sorted_values,
				size_t chunk_amount)
{
	size_t	index;
	size_t	value_index;
	size_t	pos;

	while (is_stack_ordered(ps_data->stack_a.head) == 0)
	{
		value_index = 0;
		while (value_index < chunk_amount
			&& value_index < ps_data->stack_a.list_size)
		{
			index = check_closest_value(ps_data->stack_a, sorted_values,
					chunk_amount, value_index);
			pos = find_value_position(ps_data->stack_a, sorted_values[index]);
			swap_values(&sorted_values[value_index], &sorted_values[index]);
			push_value_to_b(ps_data, pos);
			value_index++;
		}
		sorted_values = &sorted_values[value_index];
	}
}

t_error_flag	medium_algo(t_push_swap_data *ps_data)
{
	ssize_t	*sorted_values;
	size_t	chunk_amount;

	if (create_sorted_tab(&sorted_values, ps_data->stack_a) == MALLOC_ERR)
		return (MALLOC_ERR);
	chunk_amount = ft_square_root(ps_data->stack_a.list_size);
	browse_array(ps_data, sorted_values, chunk_amount);
	while (ps_data->stack_a.list_size > 0)
		call_operation(PUSH_B, ps_data);
	while (ps_data->stack_b.list_size > 0)
		push_value_to_a(ps_data, find_maximal_value(ps_data->stack_b));
	free(sorted_values);
	return (NO_ERR);
}
