#include "push_swap.h"

static int	flag_verification(char *argv)
{
	if (!ft_strcmp(argv, "--simple"))
		return (1);
	if (!ft_strcmp(argv, "--medium"))
		return (2);
	if (!ft_strcmp(argv, "--complex"))
		return (3);
	if (!ft_strcmp(argv, "--adaptive"))
		return (4);
	if (!ft_strcmp(argv, "--bench"))
		return (5);
	return (0);
}

static t_error_flag	set_flag(int check_flag, t_parsed_data *parsed_data)
{
	if (check_flag == 5)
	{
		if (parsed_data->bench_flag != TRUE)
			parsed_data->bench_flag = TRUE;
		else
			return (DUP_FLAG_ERR);
	}
	else if (check_flag > 0)
	{
		if (parsed_data->algo_flag == UNSET)
			parsed_data->algo_flag = check_flag - 1;
		else
			return (DUP_FLAG_ERR);
	}
	else
		if (parsed_data->algo_flag == UNSET)
			parsed_data->algo_flag = ADAPTIVE;
	return (NO_ERR);
}

t_error_flag	get_flags(int *argc, char ***argv, t_parsed_data *parsed_data)
{
	size_t	index;
	size_t	check_flag;

	index = 1;
	check_flag = 0;
	while (index <= 2 && (int)index < *argc)
	{
		check_flag = flag_verification((*argv)[index]);
		if (set_flag(check_flag, parsed_data) != NO_ERR)
			return (DUP_FLAG_ERR);
		if (check_flag == 0)
			break ;
		index++;
	}
	if ((int)index < *argc)
	{
		(*argv) = &(*argv)[index];
		*argc = (*argc) - index;
	}
	return (NO_ERR);
}
