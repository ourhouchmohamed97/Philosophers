/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:59 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/19 16:30:51 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	action_msg(philo, TAKE_FORK);
	pthread_mutex_lock(philo->right_fork);
	action_msg(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->data->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->m_last_meal);
	action_msg(philo, EAT);
	waiting(philo->data->eat_time, philo->data);
	if (!is_sim_end(philo->data))
	{
		pthread_mutex_lock(&philo->data->m_meals_eaten);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->m_meals_eaten);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	rest(t_philo *philo)
{
	action_msg(philo, SLEEP);
	waiting(philo->data->sleep_time, philo->data);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->m_last_meal);
	philo->last_meal = philo->data->dinner_start_time;
	pthread_mutex_unlock(&philo->data->m_last_meal);
	synch_start(philo->data->dinner_start_time);
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		action_msg(philo, TAKE_FORK);
		pthread_mutex_unlock(philo->left_fork);
		waiting(philo->data->die_time, philo->data);
		return (NULL);
	}
	action_msg(philo, THINK);
	if (philo->id % 2)
		waiting(philo->data->eat_time / 2, philo->data);
	while (!is_sim_end(philo->data))
	{
		eat(philo);
		rest(philo);
		action_msg(philo, THINK);
	}
	return (NULL);
}
