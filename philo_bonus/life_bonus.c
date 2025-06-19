/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:14:16 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/19 21:48:58 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	has_philosopher_died(t_philo *philo)
{
	size_t	t_since_last_meal;

	sem_wait(philo->sem_last_meal);
	t_since_last_meal = get_time() - philo->last_meal;
	sem_post(philo->sem_last_meal);
	return (t_since_last_meal > philo->data->die_time);
}

int	eat_enough(t_philo *philo)
{
	int	ate_enough;

	ate_enough = 1;
	if (philo->data->meals2consume)
	{
		sem_wait(philo->sem_meals_eaten);
		if (philo->meals_eaten < philo->data->meals2consume)
			ate_enough = 0;
		sem_post(philo->sem_meals_eaten);
	}
	return (philo->data->meals2consume && ate_enough);
}

void	*life_monitor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		if (has_philosopher_died(philo))
		{
			sem_wait(philo->data->sem_print);
			printf("%lld %zu died\n",
				get_time() - philo->data->dinner_start_time, philo->id);
			sem_post(philo->data->sem_end);
			exit(EXIT_FAILURE);
		}
		usleep(1000);
	}
	return (NULL);
}
