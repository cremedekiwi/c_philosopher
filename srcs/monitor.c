/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:53:02 by jarumuga          #+#    #+#             */
/*   Updated: 2024/09/11 18:38:17 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philo.h>

// checks if a philo has died by comp the curr time with the last time they ate
	// get the current time
	// calculate time to die
	// check last meal time
	// compare times
static bool	philo_died(t_philo *philo)
{
	long	current_time;
	long	t_to_die;

	current_time = get_time(MILLISECOND);
	t_to_die = philo->table->time_to_die / 1e3;
	if (current_time - get_long(&philo->philo_mutex, \
	&philo->last_meal_time) >= t_to_die)
		return (true);
	return (false);
}

// runs in a separate thread and monitors the philo to detect when one die
	// wait for all threads to start
	// main monitoring loop
		// until the sim is finished
		// check if any of them have died
			// if found to have died, sets the end_simulation to true
			// print the death
			// breaks out
	// sleep between checks
void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, \
	&table->threads_running_nbr, table->philo_nbr))
		usleep(100);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
				break ;
			}
		}
		precise_usleep(500, table);
	}
	return (NULL);
}
