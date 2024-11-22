/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:27:00 by jarumuga          #+#    #+#             */
/*   Updated: 2024/09/11 17:33:46 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philo.h>

// if (arguments check)
	// processes or validates the input arguments
	// initializes the data structures
	// begins the philosopher simulation
	// clean up after the simulation has ended.
// else
	// prints an error message
int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&table, av) == -1)
			return (1);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		print_error(R"4 or 5 arguments needed\n"RST
			G"example 5 800 200 200 1\n"RST
			"number_of_philosophers\n"
			"time_to_die\n"
			"time_to_eat\n"
			"time_to_sleep\n"
			"[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	return (0);
}
