#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_parsed_data	parsed_data;
	t_error_flag	error_flag;

	error_flag = NO_ERR;
	if (argc > 1)
	{
		error_flag = parsing(argc, argv, &parsed_data);
		if (error_flag == NO_ERR)
			error_flag = push_swap(parsed_data);
	}
	if (error_flag != NO_ERR)
		ft_fprintf(2, "Error\n");
	return (error_flag);
}
