/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:13:00 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/21 18:28:12 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*termination(void *philos_ptr)
{
	t_philo	**philos;
	t_data	*data;

	philos = (t_philo **)philos_ptr;
	data = philos[0]->data;
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

void	*check_eat_enough(void *philos_ptr)
{
	t_philo	**philos;
	t_data	*data;
	size_t	done_eating;

	done_eating = 0;
	philos = (t_philo **)philos_ptr;
	data = philos[0]->data;
	while (done_eating < data->num_philos - 1)
	{
		if (is_sim_end(data))
			return (NULL);
		sem_wait(data->sem_eat_full);
		if (!is_sim_end(data))
			done_eating++;
		else
			return (NULL);
	}
	sem_post(data->sem_end);
	return (NULL);
}

void	setup_end_detector(t_data *data, t_philo **philos)
{
	pthread_t	thread_death;
	pthread_t	thread_meal;

	if (pthread_create(&thread_death, NULL, &termination, philos) != 0)
		kill_all_philo(data, philos);
	if (data->meals2consume)
	{
		if (pthread_create(&thread_meal, NULL, &check_eat_enough, philos) != 0)
			kill_all_philo(data, philos);
		if (pthread_join(thread_meal, NULL) != 0)
			kill_all_philo(data, philos);
	}
	if (pthread_join(thread_death, NULL) != 0)
		kill_all_philo(data, philos);
}

