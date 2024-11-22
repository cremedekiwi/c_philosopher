/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:49:20 by jarumuga          #+#    #+#             */
/*   Updated: 2024/09/11 17:56:07 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philo.h>

// retrieves the current time based on the time unit specified by time_code
	// call gettimeofday
	// convert to the requested time unit
long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		print_error("gettimeofday() failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		print_error("Invalid time code");
	return (42);
}

// simulates a "precise" sleep for a specified number of microseconds
	// get the start time
	// busy-wait loop
		// if the sim has finished, breaks out of the loop and stops early
		// it calculates how much time has passed (elapsed)
		// and how much remains (rem)
	// recursive sleep
	// final precise wait : enters a loop until the full usec time has passed
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			precise_usleep(rem / 2, table);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

// cleans up resources after the simulation ends
	// destroy philosopher mutexes
	// destroy table mutexes
	// free allocated memory
void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

// prints an error message to the standard error
void	print_error(const char *error)
{
	int	len;

	len = 0;
	while (error[len])
		len++;
	write(2, error, len);
	write(2, "\n", 1);
}
