#include "push_swap.h"

static t_error_flag	is_value_invalid(char *string, ssize_t *value)
{
	size_t	index;

	index = 0;
	if (string[index] == '-' || string[index] == '+')
		index++;
	while (string[index])
	{
		if (ft_isdigit(string[index]) == 0)
			return (VALUE_ARG_ERR);
		if (index > 10)
			return (ILLEGAL_VALUE_ERR);
		index++;
	}
	*value = ft_atoll(string);
	if (*value > __INT_MAX__ || *value < __INT_MAX__ * (-1) - 1)
		return (ILLEGAL_VALUE_ERR);
	return (NO_ERR);
}

static t_error_flag	value_list_add_back(t_stack_info *stack_a,
	t_node *value_node, size_t *value_pairs, size_t *values_disordered)
{
	t_node			*temp;
	t_error_flag	dup_flag;

	temp = stack_a->head;
	dup_flag = NO_ERR;
	while (temp != NULL)
	{
		if (temp->value == value_node->value)
			dup_flag = DUP_VALUE_ERR;
		if (value_node->value < temp->value)
			(*values_disordered)++;
		(*value_pairs)++;
		temp = temp->next;
	}
	stack_a->tail->next = value_node;
	value_node->prev = stack_a->tail;
	stack_a->tail = value_node;
	return (dup_flag);
}

static t_error_flag	append_value_list(t_stack_info *stack_a,
	ssize_t value, size_t *value_pairs, size_t *values_disordered)
{
	t_node	*value_node;

	value_node = (t_node *)malloc(sizeof(t_node));
	if (value_node == NULL)
		return (MALLOC_ERR);
	value_node->prev = NULL;
	value_node->next = NULL;
	value_node->value = value;
	if (stack_a->head == NULL)
	{
		stack_a->head = value_node;
		stack_a->tail = value_node;
	}
	else if (value_list_add_back(stack_a, value_node,
			value_pairs, values_disordered) != NO_ERR)
		return (DUP_VALUE_ERR);
	return (NO_ERR);
}

static t_error_flag	compute_value_args(size_t argc, char **raw_values,
	t_parsed_data *parsed_data)
{
	size_t			index;
	ssize_t			value;
	size_t			disorder_calculus[2];
	t_error_flag	error_flag;

	index = 0;
	disorder_calculus[0] = 0;
	disorder_calculus[1] = 0;
	while (raw_values[index] && (index < argc || argc == 1))
	{
		value = 0;
		error_flag = is_value_invalid(raw_values[index], &value);
		if (error_flag != NO_ERR)
			return (error_flag);
		error_flag = append_value_list(&parsed_data->stack_a,
				value, &disorder_calculus[0], &disorder_calculus[1]);
		if (error_flag != NO_ERR)
			return (error_flag);
		index++;
	}
	disorder_calculus[1] *= 10000;
	if (disorder_calculus[0] != 0)
		parsed_data->disorder = disorder_calculus[1] / disorder_calculus[0];
	parsed_data->stack_a.list_size = index;
	return (NO_ERR);
}

t_error_flag	compute_values(int argc, char *argv[],
	t_parsed_data *parsed_data)
{
	t_error_flag	error_flag;
	char			**raw_values;
	size_t			index;

	error_flag = NO_ERR;
	if (argc == 1)
		raw_values = ft_split(*argv, ' ');
	else
		raw_values = argv;
	if (raw_values == NULL)
		return (MALLOC_ERR);
	error_flag = compute_value_args(argc, raw_values, parsed_data);
	if (argc == 1)
	{
		index = 0;
		while (raw_values[index] != NULL)
		{
			free(raw_values[index]);
			index++;
		}
		free(raw_values);
	}
	return (error_flag);
}
