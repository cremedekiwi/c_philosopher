/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:18:50 by jarumuga          #+#    #+#             */
/*   Updated: 2024/10/30 11:31:52 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philo.h>

// handles the simulation for the case where there is only one philosopher
	// initialize the philosopher
	// pick up the single fork
	// simulation loop : check if they have died
	// sleep precision
void	*lone_philo(void *arg)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, \
	get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex, \
	&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
	{
		current_time = get_time(MILLISECOND);
		if (current_time - philo->last_meal_time >= 10)
		{
			write_status(DIED, philo, DEBUG_MODE);
			break ;
		}
		precise_usleep(1000, philo->table);
	}
	return (NULL);
}

// simulates the philosopher thinking
	// log thinking
	// handle odd number of philosophers : if even, return
	// calculate thinking time, and it ensures the value is non-negative
	// simulate thinking
void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

// simulates the philosopher's eating
	// lock the first fork
	// lock the second fork
	// set last meal time
	// increment meal counter
	// simulate eating
	// mark as full
	// unlock the forks
static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, \
	get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 && \
	philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

// handles the dining simulation for each philosophers
	// initialize the philosopher
	// main simulation loop : eat, sleep then think
	// exit the loop
void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, \
	get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex, \
	&philo->table->threads_running_nbr);
	de_syncronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		current_time = get_time(MILLISECOND);
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

// starts the dining philosopher simulation
	// handle no meals case
	// handle one philosopher
	// handle multiple philosophers
	// start the monitor
	// set simulation start time
	// signal threads to start
	// join philosopher threads
	// join monitor thread
void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, , \
		&table->philos[0], CREATE);
	else
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, \
			dinner_simulation, &table->philos[i], CREATE);
	if (table->philo_nbr > 1)
		safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	if (table->philo_nbr > 1)
		safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
