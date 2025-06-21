/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:08:57 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/21 09:01:32 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	action_msg(philo, TAKE_FORK);
	sem_wait(philo->data->sem_forks);
	action_msg(philo, TAKE_FORK);
	action_msg(philo, EAT);
	sem_wait(philo->sem_last_meal);
	philo->last_meal = get_time();
	sem_post(philo->sem_last_meal);
	waiting(philo->data->eat_time);
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
	sem_wait(philo->sem_meals_eaten);
	philo->meals_eaten++;
	sem_post(philo->sem_meals_eaten);
}

void	rest(t_philo *philo)
{
	action_msg(philo, SLEEP);
	waiting(philo->data->sleep_time);
}

int	solo_philo(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	action_msg(philo, TAKE_FORK);
	sem_post(philo->data->sem_forks);
	waiting(philo->data->die_time);
	printf("%lld %zu died\n",
		get_time() - philo->data->dinner_start_time, philo->id);
	exit(EXIT_FAILURE);
}

int	philo_routine(t_philo *philo)
{
	synch_start(philo->data->dinner_start_time);
	if (philo->data->num_philos == 1)
		return (solo_philo(philo));
	if (pthread_create(&philo->life_monitor, NULL, &life_monitor, philo))
		return (INIT_ERR);
	action_msg(philo, THINK);
	if (philo->id % 2)
		waiting(philo->data->eat_time / 2);
	while (1)
	{
		eat(philo);
		rest(philo);
		action_msg(philo, THINK);
		if (eat_enough(philo))
		{
			sem_post(philo->data->sem_eat_full);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}
