/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:02:37 by jarumuga          #+#    #+#             */
/*   Updated: 2024/09/11 18:24:48 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philo.h>

// print debug information about the current status of a philosopher
static void	write_status_debug(t_philo_status status, t_philo *philo, \
long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the first fork" \
		"\t\t\t"B"[ %d ]\n"RST, elapsed, philo->id, philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the second fork" \
		"\t\t\t"B"[ %d ]\n"RST, elapsed, philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(W"%6ld"C" %d is eating" \
		"\t\t\t"Y"[ %ld ]\n"RST, elapsed, philo->id, philo->meals_counter);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(W"%6ld"RST" %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf(R"\t\t%6ld %d died\n"RST, elapsed, philo->id);
}

// printing the status of the philosopher
void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if (!simulation_finished(philo->table))
		{
			if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
				printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
			else if (status == EATING)
				printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
			else if (status == SLEEPING)
				printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
			else if (status == THINKING)
				printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		}
		if (status == DIED)
			printf(R"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
