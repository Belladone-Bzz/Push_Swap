#include "push_swap.h"

static void	benching(t_push_swap_data ps_data,
	t_algo_flag used_algorithm, size_t disorder, t_algo_flag algo_flag)
{
	char	*algorithm_names[4];
	char	*algorithm_complexities[4];
	size_t	*ops;

	algorithm_names[0] = "Simple";
	algorithm_names[1] = "Medium";
	algorithm_names[2] = "Complex";
	algorithm_names[3] = "Adaptive";
	algorithm_complexities[0] = "O(n²)";
	algorithm_complexities[1] = "O(n√n)";
	algorithm_complexities[2] = "O(nlogn)";
	ops = ps_data.operations_used;
	ft_fprintf(2, "[bench] disorder: %d,", disorder / 100);
	if (disorder % 100 < 10)
		ft_fprintf(2, "0");
	ft_fprintf(2, "%d%%\n", disorder % 100);
	ft_fprintf(2, "[bench] strategy: %s / %s\n", algorithm_names[algo_flag],
		algorithm_complexities[used_algorithm]);
	ft_fprintf(2, "[bench] total_ops: %lld\n", ps_data.number_of_operations);
	ft_fprintf(2, "[bench] sa: %lld sb: %lld ss: %lld pa: %lld pb: %lld\n",
		ops[0], ops[3], ops[6], ops[9], ops[10]);
	ft_fprintf(2, "[bench] ra: %lld rb: %lld ", ops[1], ops[4]);
	ft_fprintf(2, "rr: %lld rra: %lld rrb: %lld rrr: %lld\n",
		ops[7], ops[2], ops[5], ops[8]);
}

static void	initiate_operations_counts(t_push_swap_data *ps_data)
{
	size_t	index;

	ps_data->number_of_operations = 0;
	ps_data->stack_b.head = NULL;
	ps_data->stack_b.tail = NULL;
	ps_data->stack_b.list_size = 0;
	index = 0;
	while (index < 11)
	{
		ps_data->operations_used[index] = 0;
		index++;
	}
}

static t_algo_flag	choose_algorithm(t_parsed_data parsed_data)
{
	if (parsed_data.stack_a.list_size <= 10)
		return (SIMPLE);
	else if (parsed_data.stack_a.list_size <= 100)
		return (MEDIUM);
	else
	{
		if (parsed_data.disorder <= 800)
			return (SIMPLE);
		else if (parsed_data.disorder <= 4400)
			return (MEDIUM);
		else
			return (COMPLEX);
	}
}

void	free_stack(t_node **value_list)
{
	t_node	*temp;

	while (*value_list != NULL)
	{
		temp = (*value_list)->next;
		free(*value_list);
		*value_list = temp;
	}
	*value_list = NULL;
}

t_error_flag	push_swap(t_parsed_data parsed_data)
{
	t_push_swap_data	ps_data;
	t_algo_flag			used_algorithm;
	t_error_flag		error_flag;

	t_error_flag (*algo_functions[3])(t_push_swap_data *);
	algo_functions[SIMPLE] = &simple_algo;
	algo_functions[MEDIUM] = &medium_algo;
	algo_functions[COMPLEX] = &complex_algo;
	if (parsed_data.algo_flag == ADAPTIVE)
		used_algorithm = choose_algorithm(parsed_data);
	else
		used_algorithm = parsed_data.algo_flag;
	initiate_operations_counts(&ps_data);
	ps_data.stack_a = parsed_data.stack_a;
	error_flag = NO_ERR;
	if (parsed_data.disorder != 0)
		error_flag = algo_functions[used_algorithm](&ps_data);
	free_stack(&ps_data.stack_a.head);
	free_stack(&ps_data.stack_b.head);
	if (parsed_data.bench_flag && error_flag == NO_ERR)
		benching(ps_data, used_algorithm,
			parsed_data.disorder, parsed_data.algo_flag);
	return (error_flag);
}
