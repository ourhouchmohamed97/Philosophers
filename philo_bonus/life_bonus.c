/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:14:16 by mourhouc          #+#    #+#             */
/*   Updated: 2025/04/30 16:18:02 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * check if a philo is dead
 * => time_since_last_meal >= dieTime
 */
int	has_philosopher_died(t_philo *philo)
{
	size_t	t_since_last_meal;

	sem_wait(philo->sem_last_meal);
	t_since_last_meal = get_time() - philo->last_meal;
	sem_post(philo->sem_last_meal);
	return (t_since_last_meal > philo->data->dieTime);
}

/**
 * check if philo has eaten enough
 */
int	eat_enough(t_philo *philo)
{
	int	ate_enough;

	ate_enough = 1;
	if (philo->data->mealsToConsume)
	{
		sem_wait(philo->sem_meals_eaten);
		if (philo->meals_eaten < philo->data->mealsToConsume)
			ate_enough = 0;
		sem_post(philo->sem_meals_eaten);
	}
	return (philo->data->mealsToConsume && ate_enough);
}

/**
 * check every 0.1ms if the philo is dead or if every philo has eaten enough
 * use the mutex last meal, and dieTime to know
 * increment sem_eat_full if philo has eat enough
 */
void	*life_monitor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	sem_wait(philo->data->sem_eat_full);
	sem_wait(philo->data->sem_end);
	synch_start(philo->data->dinner_start_time);
	while (1)
	{
		if (has_philosopher_died(philo))
		{
			sem_post(philo->data->sem_end);
			action_msg(philo, DIE);
			return (NULL);
		}
		else if (eat_enough(philo))
		{
			sem_post(philo->data->sem_eat_full);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}