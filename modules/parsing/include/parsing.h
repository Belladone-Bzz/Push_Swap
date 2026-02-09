#ifndef PARSING_H
# define PARSING_H

# include "../../../include/push_swap.h"

typedef enum e_error_flag		t_error_flag;
typedef struct s_parsed_data	t_parsed_data;

/*
The parsing module is accessible through this parsing function exposed in the 
header file. It takes the reference of the structure for the parsed user 
arguments and initiates its variables before calling get_flags and 
compute_values.

Returned value : the called functions error_flag, NO_ERR, DUP_FLAG_ERR, 
VALUE_ARG_ERR, DUP_VALUE_ERR or ILLEGAL_VALUE_ERR
*/
t_error_flag	parsing(int argc, char *argv[], t_parsed_data *parsed_data);

/*
The get_flags function is the only exposed function here. The get_flag 
function manages, check and put in memory the flags given concerning the 
algorithm used and the use of bench mode. We consider that flags should be 
placed at the beginning of the list of arguments.
get_flag first calls a function that checks that the second argument 
(the one after the executable name) is a valid flag. If so, it will be 
stored in memory in the t_parsed_data structure. get_flag will check whether 
the third argument is also a valid flag. If so, it will then check that there 
are no duplicates (i.e., two bench flags or two algorithm type flags).
If valid flags have been detected, the get flag function ensures that the argv 
pointer then points to the argument located after the last valid flag detected.

Returned value : NO_ERR or DUP_FLAG_ERR
*/
t_error_flag	get_flags(int *argc, char **argv[], t_parsed_data *parsed_data);

/*
The compute_values function recovers arg if existent and place each value in a 
chained list, checking that they are not doubled and comprised between INT_MIN 
and INT_MAX. The browsing of the list to add each value is also used to 
calculate disorder, and all informations are added to the parsed_data 
structure passed by reference.
Functions : compute_values checks if arg is a single string or multiple, 
making sure that if it's unique, to split it before passing the `char **` to 
the reading-values function.
compute_value_args transforms a string into an int, checking the whole string 
is made of numbers and that this number is an actual int, before applying and 
adding atoi() to a chained list.

Returned value : NO_ERR, VALUE_ARG_ERR (an arg contains something other than 
numbers), ILLEGAL_VALUE_ERR(value is out of INT range), 
DUP_VALUE_ERR(value has a duplicate)
*/
t_error_flag	compute_values(int argc, char *argv[],
					t_parsed_data *parsed_data);

#endif