/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:59 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/08 16:27:03 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * wait little bit then check the life of the philo, then re-wait
 */
void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	action_msg(philo, TAKE_FORK);
	pthread_mutex_lock(philo->right_fork);
	action_msg(philo, TAKE_FORK);
	action_msg(philo, EAT);
	pthread_mutex_lock(&philo->data->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->m_last_meal);
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

/**
 * time to think =
 *
 * 	=> 0 if: die_time - (time_since_last_meal + eat_time) <= 0
 * 	=> 200 if > 600 ms to think
 */
// void	think(t_philo *philo)
// {
// 	long long	time_to_think;
// 	long long	to_starvation;

// 	pthread_mutex_lock(&philo->data->m_last_meal);
// 	time_to_think = (philo->data->die_time);
// 	to_starvation = ((get_time() - philo->last_meal) + philo->data->eat_time);
// 	pthread_mutex_unlock(&philo->data->m_last_meal);
// 	if (to_starvation >= time_to_think)
// 		time_to_think = 0;
// 	else
// 	{
// 		time_to_think -= to_starvation;
// 		time_to_think /= 2;
// 		if (time_to_think > 500)
// 			time_to_think = 150;
// 	}
// 	action_msg(philo, THINK);
// 	waiting(time_to_think, philo->data);
// 	return ;
// }

// void think(t_philo *philo)
// {
//     long long	available_time;

//     // Calculate how much time we have left
//     available_time = philo->data->die_time - philo->data->eat_time - philo->data->sleep_time;
//     if (available_time <= 0)
//         return; // No thinking time - too risky
//     action_msg(philo, THINK);
//     waiting(available_time / 4, philo->data); // Think for 1/4 of buffer time
// }
void think(t_philo *philo)
{
    long long	available_time;
	long long	time_since_meal;

	pthread_mutex_lock(&philo->data->m_last_meal);
	time_since_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->m_last_meal);	
	// Calculate available thinking time to prevent death
	available_time = philo->data->die_time - time_since_meal 
		- philo->data->eat_time;
    action_msg(philo, THINK);
    if (available_time > 0)
	{
		if (available_time > 200)
			waiting(available_time / 4, philo->data);
		else if (available_time > 50)
			waiting(10, philo->data);
		// If very little time, don't wait at all
	}
}

/**
 * the daily philo_routine of each philosopher
 * 		- eat()
 * 		- sleep()
 * 		- think()
 *
 */
void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->m_last_meal);
	philo->last_meal = philo->data->dinner_start_time;
	pthread_mutex_unlock(&philo->data->m_last_meal);
	synch_start(philo->data->dinner_start_time);
	think(philo);
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		action_msg(philo, TAKE_FORK);
		pthread_mutex_unlock(philo->left_fork);
		waiting(philo->data->die_time, philo->data);
		return (NULL);
	}
	if (philo->id % 2)
		waiting(philo->data->eat_time / 2, philo->data);
	while (!is_sim_end(philo->data))
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (NULL);
}
