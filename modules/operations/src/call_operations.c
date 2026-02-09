#include "push_swap.h"

static void	swap(t_operations op_flag, t_stack_info *stack)
{
	ssize_t	temp;

	if (stack->list_size > 1)
	{
		temp = stack->head->next->value;
		stack->head->next->value = stack->head->value;
		stack->head->value = temp;
	}
	if (op_flag == SWAP_A)
		ft_printf("sa\n");
	else if (op_flag == SWAP_B)
		ft_printf("sb\n");
	else if (op_flag == SWAP_S)
		ft_printf("ss\n");
}

static void	rotate(t_operations op_flag, t_stack_info *stack)
{
	t_node	*temp;

	if (stack->list_size > 1)
	{
		stack->tail->next = stack->head;
		stack->head->prev = stack->tail;
		temp = stack->head->next;
		stack->head->next = NULL;
		stack->tail = stack->head;
		stack->head = temp;
		stack->head->prev = NULL;
	}
	if (op_flag == ROTATE_A)
		ft_printf("ra\n");
	else if (op_flag == ROTATE_B)
		ft_printf("rb\n");
	else if (op_flag == ROTATE_S)
		ft_printf("rr\n");
}

static void	r_rotate(t_operations op_flag, t_stack_info *stack)
{
	t_node	*temp;

	if (stack->list_size > 1)
	{
		stack->head->prev = stack->tail;
		stack->tail->next = stack->head;
		temp = stack->tail->prev;
		stack->tail->prev = NULL;
		stack->head = stack->tail;
		stack->tail = temp;
		stack->tail->next = NULL;
	}
	if (op_flag == R_ROTATE_A)
		ft_printf("rra\n");
	else if (op_flag == R_ROTATE_B)
		ft_printf("rrb\n");
	else if (op_flag == R_ROTATE_S)
		ft_printf("rrr\n");
}

static void	push(t_operations op_flag,
	t_stack_info *stack_src, t_stack_info *stack_dst)
{
	t_node	*new_head;

	if (stack_src->list_size > 0)
	{
		new_head = stack_src->head;
		stack_src->head = stack_src->head->next;
		if (stack_src->head != NULL)
			stack_src->head->prev = NULL;
		if (stack_src->head == NULL)
			stack_src->tail = NULL;
		new_head->next = stack_dst->head;
		if (stack_dst->head != NULL)
			stack_dst->head->prev = new_head;
		stack_dst->head = new_head;
		if (stack_dst->list_size == 0)
			stack_dst->tail = new_head;
		stack_src->list_size--;
		stack_dst->list_size++;
	}
	if (op_flag == PUSH_A)
		ft_printf("pa\n");
	else if (op_flag == PUSH_B)
		ft_printf("pb\n");
}

t_error_flag	call_operation(t_operations op_flag, t_push_swap_data *ps_data)
{
	void	(*op_functions[3])(t_operations op_flag, t_stack_info *stack);

	op_functions[0] = &swap;
	op_functions[1] = &rotate;
	op_functions[2] = &r_rotate;
	if (op_flag <= R_ROTATE_A)
		op_functions[op_flag % 3](op_flag, &ps_data->stack_a);
	else if (op_flag <= R_ROTATE_B)
		op_functions[op_flag % 3](op_flag, &ps_data->stack_b);
	else if (op_flag <= R_ROTATE_S)
	{
		op_functions[op_flag % 3](NO_PRINT, &ps_data->stack_a);
		op_functions[op_flag % 3](op_flag, &ps_data->stack_b);
	}
	else if (op_flag <= PUSH_A)
		push(op_flag, &ps_data->stack_b, &ps_data->stack_a);
	else if (op_flag <= PUSH_B)
		push(op_flag, &ps_data->stack_a, &ps_data->stack_b);
	else
		return (OPERATION_ERR);
	ps_data->operations_used[op_flag]++;
	ps_data->number_of_operations++;
	return (NO_ERR);
}
