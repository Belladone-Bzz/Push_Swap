#include "push_swap.h"

void	swap_values(ssize_t *ptr1, ssize_t *ptr2)
{
	ssize_t	temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

static void	sort_tab(t_node *head, size_t list_size, ssize_t *array)
{
	size_t	index;
	size_t	index_b;

	index = 0;
	while (head != NULL)
	{
		array[index] = head->value;
		head = head->next;
		index++;
	}
	index = 0;
	while (index < list_size - 1)
	{
		index_b = index + 1;
		while (index_b < list_size)
		{
			if (array[index] > array[index_b])
				swap_values(&array[index], &array[index_b]);
			index_b++;
		}
		index++;
	}
}

t_error_flag	create_sorted_tab(ssize_t **sorted_values, t_stack_info stack)
{
	ssize_t	list_size;

	list_size = stack.list_size;
	*sorted_values = (ssize_t *)malloc(sizeof(ssize_t) * list_size);
	if (*sorted_values == NULL)
		return (MALLOC_ERR);
	sort_tab(stack.head, list_size, *sorted_values);
	return (NO_ERR);
}
