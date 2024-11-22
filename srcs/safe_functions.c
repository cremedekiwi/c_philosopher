/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarumuga <jarumuga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:16:23 by jarumuga          #+#    #+#             */
/*   Updated: 2024/09/11 18:50:15 by jarumuga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/philo.h>

// wrapper around the standard malloc to handle memory allocation errors
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		print_error("Malloc error");
		return (NULL);
	}
	return (ret);
}

// handle mutex-related errors based on the status returned by mutex operations
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
	{
		if (opcode == LOCK || opcode == UNLOCK)
			print_error("The value specified by mutex is invalid");
		else if (opcode == INIT)
			print_error("The value specified by attr is invalid");
	}
	else if (status == EDEADLK)
		print_error("A deadlock would occur \
		if the thread blocked waiting for mutex");
	else if (status == EPERM)
		print_error("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		print_error("The process cannot allocate enough memory \
		to create another mutex");
	else if (status == EBUSY)
		print_error("Mutex is locked");
}

// safe wrapper around various mutex operations
int	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	int	status;

	status = 0;
	if (opcode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
	{
		print_error("Invalid opcode");
		return (-1);
	}
	handle_mutex_error(status, opcode);
	return (status);
}

// handle thread-related errors based on the status returned by operations
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		print_error("No resources available to create another thread");
	else if (status == EPERM)
		print_error("The caller does not have appropriate permission");
	else if (status == EINVAL && opcode == CREATE)
		print_error("The value specified by attr is invalid");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		print_error("The specified thread is not joinable");
	else if (status == ESRCH)
		print_error("No thread could be found with the given thread ID");
	else if (status == EDEADLK)
		print_error("A deadlock was detected");
}

// wrapper around various thread operations
int	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), \
void *data, t_opcode opcode)
{
	int	status;

	status = 0;
	if (opcode == CREATE)
		status = pthread_create(thread, NULL, foo, data);
	else if (opcode == JOIN)
		status = pthread_join(*thread, NULL);
	else if (opcode == DETACH)
		status = pthread_detach(*thread);
	else
	{
		print_error("Invalid opcode, use CREATE, JOIN, or DETACH");
		return (-1);
	}
	handle_thread_error(status, opcode);
	return (status);
}
