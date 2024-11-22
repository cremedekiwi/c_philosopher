/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:58:15 by jarumuga          #+#    #+#             */
/*   Updated: 2024/09/11 18:49:38 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philo.h>

// check if the char is a digit
static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

// check if the char is a whitespace
static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

// validates the input string to ensure it is a properly formatted number
	// skip spaces
	// check for sign
	// check if it's a digit
	// count digits
static char	*valid_input(char *str)
{
	int		len;
	char	*nbr;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (print_error(R"negative number"RST), NULL);
	if (!is_digit(*str))
		return (print_error(R"not a number"RST), NULL);
	nbr = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		return (print_error(R"more than 10 digits"RST), NULL);
	return (nbr);
}

// converts a string representation of a number into a long
	// validate input
	// string to number conversion
	// check for overflow
static long	ft_atol(char *str)
{
	long	nbr;

	nbr = 0;
	str = valid_input(str);
	if (!str)
		return (-1);
	if (str == 0)
		return (-1);
	while (is_digit(*str))
		nbr = (nbr * 10) + (*str++ - '0');
	if (nbr > INT_MAX)
		return (print_error(R"int max is the limit"RST), -1);
	return (nbr);
}

// store the values in the structure
	// check the first four arguments
	// check for zero values
	// check for a maximum number of philosophers
	// store values in the table
	// check for a minimum time
	// optional argument (number of meals)
int	parse_input(t_table *table, char **av)
{
	if (ft_atol(av[1]) == -1 || ft_atol(av[2]) == -1 \
	|| ft_atol(av[3]) == -1 || ft_atol(av[4]) == -1)
		return (-1);
	if (ft_atol(av[1]) == 0 || ft_atol(av[2]) == 0 \
	|| ft_atol(av[3]) == 0 || ft_atol(av[4]) == 0)
		return (print_error(R"value can't be 0"RST), -1);
	if (ft_atol(av[1]) > 200)
		return (print_error(R"not more than 200 philos"RST), -1);
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 \
	|| table->time_to_eat < 6e4 \
	|| table->time_to_sleep < 6e4)
		return (print_error(R"at least 60ms"RST), -1);
	if (av[5] && (ft_atol(av[5]) == -1))
		return (-1);
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	return (1);
}
