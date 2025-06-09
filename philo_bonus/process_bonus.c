/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:13:00 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/09 13:03:35 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * thread the monitoring process for checking if
 * the global semaphore end is set to one
 * kill all philo if it's the case.
 */
void	*termination(void *philos_ptr)
{
	t_philo	**philos;
	t_data	*data;

	philos = (t_philo **)philos_ptr;
	data = philos[0]->data;
	synch_start(data->dinner_start_time);
	sem_wait(data->sem_end);
	sem_wait(data->sem_set_end);
	data->end = 1;
	sem_post(data->sem_set_end);
	kill_all_philo(data, philos);
	return (NULL);
}

int	is_sim_end(t_data *data)
{
	int	bool_end;

	bool_end = 0;
	sem_wait(data->sem_set_end);
	bool_end = data->end;
	sem_post(data->sem_set_end);
	return (bool_end);
}

/**
 * thread the monitoring process for checking if
 * all philo has enough eat
 */
void	*check_eat_enough(void *philos_ptr)
{
	t_philo	**philos;
	t_data	*data;
	size_t	meals_eaten;

	meals_eaten = 0;
	philos = (t_philo **)philos_ptr;
	data = philos[0]->data;
	synch_start(data->dinner_start_time);
	while (meals_eaten < data->num_philos)
	{
		if (is_sim_end(data))
			return (NULL);
		sem_wait(data->sem_eat_full);
		if (!is_sim_end(data))
			meals_eaten++;
		else
			return (NULL);
	}
	sem_wait(data->sem_print);
	printf("%sAll philosophers have eaten enough meals!%s\n", GREEN, NC);
	sem_post(data->sem_print);
	sem_post(data->sem_end);
	return (NULL);
}

void	stop_simulation(t_data *data, t_philo **philos)
{
	pthread_t	thread_death;
	pthread_t	thread_meal;

	if (pthread_create(&thread_death, NULL, &termination, philos))
		kill_all_philo(data, philos);
	if (data->meals2consume)
	{
		if (pthread_create(&thread_meal, NULL, &check_eat_enough, philos))
			kill_all_philo(data, philos);
		if (pthread_join(thread_meal, NULL))
			kill_all_philo(data, philos);
	}
	if (pthread_join(thread_death, NULL))
		kill_all_philo(data, philos);
}
