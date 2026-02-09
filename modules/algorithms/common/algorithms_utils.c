#include "push_swap.h"

size_t	find_minimal_value(t_stack_info stack)
{
	t_node	*temp;
	t_node	*memory;
	size_t	index;
	size_t	pos;

	index = 0;
	temp = stack.head;
	pos = 0;
	memory = temp;
	while (temp != NULL)
	{
		if (temp->value < memory->value)
		{
			pos = index;
			memory = temp;
		}
		temp = temp->next;
		index ++;
	}
	return (pos);
}

size_t	find_maximal_value(t_stack_info stack)
{
	t_node	*temp;
	t_node	*memory;
	size_t	index;
	size_t	pos;

	index = 0;
	temp = stack.head;
	pos = 0;
	memory = temp;
	while (temp != NULL)
	{
		if (temp->value > memory->value)
		{
			pos = index;
			memory = temp;
		}
		temp = temp->next;
		index ++;
	}
	return (pos);
}

size_t	is_stack_ordered(t_node *head)
{
	while (head != NULL)
	{
		if (head->next != NULL && head->next->value < head->value)
			return (0);
		head = head->next;
	}
	return (1);
}

void	push_value_to_a(t_push_swap_data *ps_data, size_t pos)
{
	size_t	index;

	index = 0;
	if (pos >= ((ps_data->stack_b.list_size) / 2))
	{
		while (index < (ps_data->stack_b.list_size - pos))
		{
			call_operation(R_ROTATE_B, ps_data);
			index ++;
		}
	}
	if (pos < ((ps_data->stack_b.list_size) / 2))
	{
		while (index < pos)
		{
			call_operation(ROTATE_B, ps_data);
			index ++;
		}
	}
	call_operation(PUSH_A, ps_data);
}

void	push_value_to_b(t_push_swap_data *ps_data, size_t pos)
{
	size_t	index;

	index = 0;
	if (pos >= ((ps_data->stack_a.list_size) / 2))
	{
		while (index < (ps_data->stack_a.list_size - pos))
		{
			call_operation(R_ROTATE_A, ps_data);
			index ++;
		}
	}
	if (pos < ((ps_data->stack_a.list_size) / 2))
	{
		while (index < pos)
		{
			call_operation(ROTATE_A, ps_data);
			index ++;
		}
	}
	call_operation(PUSH_B, ps_data);
}
