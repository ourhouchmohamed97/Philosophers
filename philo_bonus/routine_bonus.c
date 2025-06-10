/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mourhouc <mourhouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:08:57 by mourhouc          #+#    #+#             */
/*   Updated: 2025/06/10 10:33:15 by mourhouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * take 2 fork, then eat (wait eat_time)
 * incremente meals_eaten
 * update last_meal
 **/
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

///**
// * time to think =
// *
// * 	=> 0 if: die_time - (time_since_last_meal + eat_time) <= 0
// * 	=> 200 if > 600 ms to think
// */
// void	think(t_philo *philo)
// {
// 	long long	time_to_think;
// 	long long	temp;

// 	sem_wait(philo->sem_last_meal);
// 	time_to_think = (philo->data->die_time);
// 	temp = ((get_time() - philo->last_meal) + philo->data->eat_time);
// 	sem_post(philo->sem_last_meal);
// 	if (temp >= time_to_think)
// 		time_to_think = 0;
// 	else
// 	{
// 		time_to_think -= temp;
// 		time_to_think /= 2;
// 		if (time_to_think > 500)
// 			time_to_think = 150;
// 	}
// 	action_msg(philo, THINK);
// 	waiting(time_to_think);
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
//     waiting(available_time / 4); // Think for 1/4 of buffer time
// }

void	think(t_philo *philo)
{
	long long	available_time;
	long long	time_since_meal;

	sem_wait(philo->sem_last_meal);
	time_since_meal = get_time() - philo->last_meal;
	sem_post(philo->sem_last_meal);
	
	// Calculate available thinking time to prevent death
	available_time = philo->data->die_time - time_since_meal 
		- philo->data->eat_time;
	
	action_msg(philo, THINK);
	
	// Think for a safe amount of time
	if (available_time > 0)
	{
		if (available_time > 200)
			waiting(available_time / 4);
		else if (available_time > 50)
			waiting(10);
		// If very little time, don't wait at all
	}
}

// int	solo_philo(t_philo *philo)
// {
// 	sem_wait(philo->data->sem_eat_full);
// 	sem_wait(philo->data->sem_end);
// 	synch_start(philo->data->dinner_start_time);
// 	sem_wait(philo->data->sem_forks);
// 	action_msg(philo, TAKE_FORK);
// 	sem_post(philo->data->sem_forks);
// 	waiting(philo->data->die_time);
// 	sem_post(philo->data->sem_end);
// 	action_msg(philo, DIE);
// 	return (0);
// }

/**
 * the daily philo_routine of each philosopher
 * 		- eat()
 * 		- sleep()
 * 		- think()
 *	from here, we are in child process <==> in philosopher body
 *
 */
int	philo_routine(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		// sem_wait(philo->data->sem_eat_full);
		sem_wait(philo->data->sem_end);
		synch_start(philo->data->dinner_start_time);
		sem_wait(philo->data->sem_forks);
		action_msg(philo, TAKE_FORK);
		sem_post(philo->data->sem_forks);
		waiting(philo->data->die_time);
		sem_post(philo->data->sem_end);
		action_msg(philo, DIE);
		return (0);
	}
	if (pthread_create(&philo->life_monitor, NULL, &life_monitor, philo))
		return (INIT_ERR);
	synch_start(philo->data->dinner_start_time);
	think(philo);
	if (philo->id % 2)
		waiting(philo->data->eat_time / 2);
	while (1)
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (0);
}
